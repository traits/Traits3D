#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation
#include "textengine/fonts_std_generated.h"
#include "glhelper.h"
#include "textengine_std.h"

stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs


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
  "  gl_FragColor = vec4(color, texture2D(tex, texpos).a);\n"
  "}"
  )
{
}


bool Protean3D::StandardTextEngine::initializeGL()
{
  bool bf = shader_.create(VertexCode_, FragmentCode_);
  vao_ = std::make_unique<GL::VAO>();
  vbo_ = std::make_unique<GL::VBO>(vao_.get());
  cdata.resize(96);

  unsigned char temp_bitmap[512 * 512];
  stbtt_BakeFontBitmap(&StandardFont::OpenSans_Regular_ttf[0], 0, 32.0, temp_bitmap, 512, 512, 32, 96, &cdata[0]); // no guarantee this fits!
  glGenTextures(1, &tex_atlas_);
  glBindTexture(GL_TEXTURE_2D, tex_atlas_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
  // can free temp_bitmap at this point
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  return true;
}

void Protean3D::StandardTextEngine::drawAt(float x, float y, std::string text, 
  float scale, Protean3D::Color const& color)
{
  shader_.use();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex_atlas_);
  GLuint texture_sampler = glGetUniformLocation(shader_.programId(), "tex");
  glUniform1i(texture_sampler, 0);

  int viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport); // x,y,w,h

  glm::mat4 pmat = glm::ortho<float>(
    static_cast<float>(viewport[0]), static_cast<float>(viewport[0] + viewport[2]),
    // reverse y axis
    static_cast<float>(viewport[1] + viewport[3]), static_cast<float>(viewport[1]) 
    );

  bool bf = shader_.setUniformMatrix(pmat, "proj_mat");

  shader_.setUniformVec3(glm::vec3(color.r, color.g, color.b), "color");
  int c = 0;
  std::vector<glm::vec4> coords(4 * text.size());

  for (auto ch : text)
  {
    if (ch >= 32 && ch < 128)
    {
      stbtt_aligned_quad q;
      stbtt_GetBakedQuad(&cdata[0], 512, 512, ch - 32, &x, &y, &q, 1);

      coords[c++] = glm::vec4(q.x0 * scale, q.y1 * scale, q.s0, q.t1);
      coords[c++] = glm::vec4(q.x1 * scale, q.y1 * scale, q.s1, q.t1);
      coords[c++] = glm::vec4(q.x1 * scale, q.y0 * scale, q.s1, q.t0);
      coords[c++] = glm::vec4(q.x0 * scale, q.y0 * scale, q.s0, q.t0);
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
  bf = vbo_->draw(GL_QUADS);
  //if (wireframe)
  //{
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //}
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool Protean3D::StandardTextEngine::drawText(std::string const& text)
{
  drawAt(10, 30, text, 1, Protean3D::Color(0.0f, 0.0f, 0.3f, 0.0f));
  return true;
}

bool Protean3D::StandardTextEngine::drawLabel(double val)
{
  return false;
}

