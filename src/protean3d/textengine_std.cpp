#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation
#include <numeric>
#include "textengine/fonts_std_generated.h"
#include "glhelper.h"
#include "textengine_std.h"
#include <iostream>


Protean3D::StandardTextEngine::StandardTextEngine()
  :VertexCode_(
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "in vec4 coord;\n"
  "out vec2 texpos; \n"
  "uniform mat4 proj_mat; \n"
  "void main()\n"
  "{\n"
  "  gl_Position = proj_mat * vec4(coord.xy, 0, 1); \n"
  "  texpos = coord.zw; \n"
  "}"
  ),
  FragmentCode_(
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "in vec2 texpos;\n"
  "uniform sampler2D tex;\n"
  "uniform vec3 color;\n"
  "void main()\n"
  "{\n"
  "  gl_FragColor = vec4(color, texture2D(tex, texpos).r);\n"
  "}"
  )
{
}


bool Protean3D::StandardTextEngine::initializeGL()
{
  if (!shader_.create(VertexCode_, FragmentCode_))
    return false;
  vao_ = std::make_unique<GL::VAO>();
  vbo_ = std::make_unique<GL::VBO>(vao_.get());

  const size_t glyph_cnt = 96;
  const float font_height = 32.0f;

  cdata.resize(glyph_cnt); // ASCII 32..126 is 95 glyphs

  unsigned char temp_bitmap[512 * 512];
  if (-1 == stbtt_BakeFontBitmap(&StandardFont::OpenSans_Regular_ttf[0], 0, font_height,
    temp_bitmap, 512, 512, 32, int(glyph_cnt), &cdata[0])) // no guarantee this fits!
  {
    return false;
  }
  glGenTextures(1, &tex_atlas_);
  glBindTexture(GL_TEXTURE_2D, tex_atlas_);
  // GL_RED here, because GL_ALPHA is not longer supported from newer OpenGL versions
  // requires change from .a to .r component in fragment shader too
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);
  // temp_bitmap free-able from this point
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  return true;
}


bool Protean3D::StandardTextEngine::drawText(
  std::vector<std::string> const& texts, 
  std::vector<glm::vec2> const& positions, 
  Protean3D::Color const& color)
{
  if (positions.empty() || positions.size() != texts.size())
    return false;

  shader_.use();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex_atlas_);
  GLuint texture_sampler = glGetUniformLocation(shader_.programId(), "tex");
  glUniform1i(texture_sampler, 0);

  glm::ivec4 viewport = GL::viewPort();
  glm::mat4 pmat = glm::ortho<float>(
    static_cast<float>(viewport[0]), static_cast<float>(viewport[0] + viewport[2]),
    // reverse y axis
    static_cast<float>(viewport[1] + viewport[3]), static_cast<float>(viewport[1])
    );

  bool bf = shader_.setUniformMatrix(pmat, "proj_mat");

  shader_.setUniformVec3(glm::vec3(color.r, color.g, color.b), "color");

  size_t char_cnt = 0;
  for (auto text : texts)
    char_cnt += text.size();

  std::vector<glm::vec4> coords(6 * char_cnt);

  size_t c = 0;
  size_t i = 0;
  for (auto text : texts)
  {
    float x = positions[i].x;
    float y = positions[i].y;
    ++i;
    for (auto ch : text)
    {
      if (ch >= 32 && ch < 128)
      {
        stbtt_aligned_quad q;
        stbtt_GetBakedQuad(&cdata[0], 512, 512, ch - 32, &x, &y, &q, 1);

        coords[c++] = glm::vec4(q.x0, q.y0, q.s0, q.t0);
        coords[c++] = glm::vec4(q.x0, q.y1, q.s0, q.t1);
        coords[c++] = glm::vec4(q.x1, q.y0, q.s1, q.t0);

        coords[c++] = glm::vec4(q.x0, q.y1, q.s0, q.t1);
        coords[c++] = glm::vec4(q.x1, q.y0, q.s1, q.t0);
        coords[c++] = glm::vec4(q.x1, q.y1, q.s1, q.t1);
      }
    }
  }
  bf = vbo_->setData(coords);
  bf = shader_.bindAttribute(*vbo_, "coord");


  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_DEPTH_TEST);
  //if (wireframe)
  //{
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //}
  bf = vbo_->draw(GL_TRIANGLES);
  //if (wireframe)
  //{
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //}
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  return true;
}


