#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation
#include "textengine/fonts_std_generated.h"
#include "protean3d/glbase/glhelper.h"
#include "protean3d/textengine_std.h"
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

  if (!setColor(Color(0, 0, 0, 1)))
    return false;

  glGenTextures(1, &tex_atlas_);
  glBindTexture(GL_TEXTURE_2D, tex_atlas_);
  // GL_RED here, because GL_ALPHA is not longer supported from newer OpenGL versions
  // requires change from .a to .r component in fragment shader too
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);
  // temp_bitmap free-able from this point
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  return true;
}


bool Protean3D::StandardTextEngine::setText(std::vector<std::string> const& texts)
{
  if (texts.empty())
    return false;

  texts_.resize(texts.size());
  for (auto i = 0; i != texts.size(); ++i)
  {
    texts_[i].text = texts[i];
    texts_[i].hull = Hull(); // reset //todo?
  }

  size_t char_cnt = 0;
  for (auto t : texts_)
    char_cnt += t.text.size();

  coords_.resize(quad_points * char_cnt);

  size_t c = 0;
  size_t i = 0;

  for (auto& t : texts_)
  {
    float dx = 0;
    float dy = 0;
    for (auto ch : t.text)
    {
      if (ch >= 32 && ch < 128)
      {
        stbtt_aligned_quad q;
        stbtt_GetBakedQuad(&cdata[0], 512, 512, ch - 32, &dx, &dy, &q, 1);

        coords_[c++] = glm::vec4(q.x0, q.y0, q.s0, q.t0);
        coords_[c++] = glm::vec4(q.x0, q.y1, q.s0, q.t1);
        coords_[c++] = glm::vec4(q.x1, q.y0, q.s1, q.t0);
                                   
        coords_[c++] = glm::vec4(q.x0, q.y1, q.s0, q.t1);
        coords_[c++] = glm::vec4(q.x1, q.y0, q.s1, q.t0);
        coords_[c++] = glm::vec4(q.x1, q.y1, q.s1, q.t1);

        if (q.x0 < t.hull.bl.x)
          t.hull.bl.x = q.x0;
        if (q.x1 > t.hull.tr.x)
          t.hull.tr.x = q.x1;
        if (q.y0 < t.hull.bl.y)
          t.hull.bl.y = q.y0;
        if (q.y1 > t.hull.tr.y)
          t.hull.tr.y = q.y1;
      }
    }
    ++i;
  }
  return true;
}


bool Protean3D::StandardTextEngine::drawText(std::vector<TextEngine::Position> const& positions)
{
  if (positions.size() != texts_.size())
    return false;

  for (auto i = 0; i != texts_.size(); ++i)
  {
    texts_[i].position = positions[i];
  }

  if ( !vbo_->setData(coords_)
    || !shader_.bindAttribute(*vbo_, "coord")
    || !shader_.use()
    )
    return false;

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex_atlas_);
  GLuint texture_sampler = glGetUniformLocation(shader_.programId(), "tex");
  glUniform1i(texture_sampler, 0);

  GL::State blend(GL_BLEND, GL_TRUE), depth_test(GL_DEPTH_TEST, GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //if (wireframe)
  //{
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //}

  glm::ivec4 viewport = GL::viewPort();
  size_t sidx = 0;
  size_t step = 0;

  TupleF tpos;
  for (auto t : texts_)
  {
    tpos = t.position.coordinates;
    switch (t.position.anchor)
    {
    case BottomCenter:
      tpos.x -= 0.5f * t.hull.width();
      break;
    case BottomRight: 
      tpos.x -= t.hull.width();
      break;
    case CenterLeft: 
      tpos.y -= 0.5f * t.hull.height();
      break;
    case Center: 
      tpos -= 0.5f * TupleF(t.hull.width(), t.hull.height());
      break;
    case CenterRight: 
      tpos -= TupleF(t.hull.width(), 0.5 * t.hull.height());
      break;
    case TopLeft:
      tpos.y -= t.hull.height();
      break;
    case TopCenter: 
      tpos -= TupleF(0.5f * t.hull.width(), t.hull.height());
      break;
    case TopRight: 
      tpos -= TupleF(t.hull.width(), t.hull.height());
      break;
    default:
      break;
    }
    // move viewport to make text appear at the right position
    glm::mat4 pmat = glm::ortho<float>(
      static_cast<float>(viewport[0] - tpos.x),
      static_cast<float>(viewport[0] + viewport[2] - tpos.x),
      // reverse y axis
      static_cast<float>(tpos.y),
      static_cast<float>(tpos.y - viewport[3])
      );

    shader_.setUniformMatrix(pmat, "proj_mat");
    step = quad_points *  t.text.size();
    vbo_->draw(GL_TRIANGLES, sidx, step);
    sidx += step;
  }
  //if (wireframe)
  //{
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //}

  return true;
}

bool Protean3D::StandardTextEngine::setColor(Color const &color)
{
  return shader_.setUniformVec3(glm::vec3(color.r, color.g, color.b), "color");
}