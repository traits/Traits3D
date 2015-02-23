#include "traits3d/glbase/glhelper.h"

#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation
#include "traits3d/textengine/stb_truetype.h"

#include "traits3d/fonts/stdfonts.h"
#include "traits3d/glbase/vao.h"
#include "traits3d/glbase/vbo.h"
#include "traits3d/glbase/shader.h"
#include "traits3d/textengine/textengine_std.h"

class Traits3D::StandardTextEngine::GLHider
{
public:
  GLuint atlas;
}; 

class Traits3D::StandardTextEngine::StbHider
{
public:
  std::vector<stbtt_bakedchar> bc_vec;
};


Traits3D::StandardTextEngine::~StandardTextEngine() = default;

Traits3D::StandardTextEngine::StandardTextEngine()
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
  cdata_ = std::make_unique<Traits3D::StandardTextEngine::StbHider>();
  tex_atlas_ = std::make_unique<Traits3D::StandardTextEngine::GLHider>();
}

bool Traits3D::StandardTextEngine::initializeGL()
{
  shader_ = std::make_unique<GL::Shader>();
  if (!shader_->create(VertexCode_, FragmentCode_))
    return false;
  vao_ = std::make_unique<GL::VAO>();
  vbo_ = std::make_unique<GL::VBO>(vao_.get());

  const size_t glyph_cnt = 96;
  const float font_height = 24.0f;

  cdata_->bc_vec.resize(glyph_cnt); // ASCII 32..126 is 95 glyphs

  unsigned char temp_bitmap[512 * 512];
  if (-1 == stbtt_BakeFontBitmap(&StandardFont::OpenSans_Regular.data[0], 0, font_height,
    temp_bitmap, 512, 512, 32, int(glyph_cnt), &cdata_->bc_vec[0])) // no guarantee this fits!
  {
    return false;
  }

  glGenTextures(1, &tex_atlas_->atlas);

  GLint oldtex = 0;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldtex);
  glBindTexture(GL_TEXTURE_2D, tex_atlas_->atlas);
  // GL_RED here, because GL_ALPHA is not longer supported from newer OpenGL versions
  // requires change from .a to .r component in fragment shader too
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);
  // temp_bitmap free-able from this point
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, oldtex);
  return true;
}

bool Traits3D::StandardTextEngine::setText(std::string const& text, size_t index /*= 0*/)
{
  if (index >= texts_.size() || index >= coords_.size())
    return false;

  return setText(texts_[index], coords_[index], text);
}

bool Traits3D::StandardTextEngine::setText(Text& t, Quads& qv, std::string const& text)
{
  if (text.empty())
    return false;

  if (text.empty())
    return false;

  t.text = text;
  t.hull = Hull(); // reset //todo?

  qv.resize(text.size());

  float dx = 0;
  float dy = 0;
  for (auto i = 0; i != t.text.size(); ++i)
  {
    auto& ch = t.text[i];
    if (ch >= 32 /*&& ch < 128*/)
    {
      stbtt_aligned_quad q;
      stbtt_GetBakedQuad(&cdata_->bc_vec[0], 512, 512, ch - 32, &dx, &dy, &q, 1);

      qv[i][0] = glm::vec4(q.x0, q.y0, q.s0, q.t0);
      qv[i][1] = glm::vec4(q.x0, q.y1, q.s0, q.t1);
      qv[i][2] = glm::vec4(q.x1, q.y0, q.s1, q.t0);
      qv[i][3] = glm::vec4(q.x0, q.y1, q.s0, q.t1);
      qv[i][4] = glm::vec4(q.x1, q.y0, q.s1, q.t0);
      qv[i][5] = glm::vec4(q.x1, q.y1, q.s1, q.t1);

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
  return true;
}

bool Traits3D::StandardTextEngine::setTexts(std::vector<std::string> const& texts)
{
  clear();
  for (auto t : texts)
    if (!appendText(t))
      return false;

  return true;
}

bool Traits3D::StandardTextEngine::appendText(std::string const& text)
{
  Text t;
  Quads qv;

  if (!setText(t, qv, text))
    return false;

  texts_.push_back(t);
  coords_.push_back(qv);

  return true;
}

bool Traits3D::StandardTextEngine::draw(
  std::vector<TextEngine::Position> const& positions,
  std::vector<Traits3D::Color> const& colors)
{
  if (positions.size() != texts_.size())
    return false;
  
  if (colors.size() != texts_.size())
    return false;

  for (size_t i = 0; i != texts_.size(); ++i)
  {
    texts_[i].position = positions[i];
    texts_[i].color = colors[i];
  }

  std::vector<glm::vec4> coords;
  for (auto const& text : coords_)
  {
    for (auto const& ch : text)
      coords.insert(coords.end(), ch.begin(), ch.end());
  }


  if ( !vbo_->setData(coords)
    || !shader_->bindAttribute(*vbo_, "coord")
    || !shader_->use()
    )
    return false;


  GLint oldtex = 0;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldtex);
  GLint oldactivetex = 0;
  glGetIntegerv(GL_ACTIVE_TEXTURE, &oldactivetex);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex_atlas_->atlas);
  GLuint texture_sampler = glGetUniformLocation(shader_->programId(), "tex");
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

  glm::vec2 tpos;
  for (auto t : texts_)
  {
    tpos = t.position.coordinates;
    switch (t.position.anchor)
    {
    case Anchor::BottomCenter:
      tpos.x -= 0.5f * t.hull.width();
      break;
    case Anchor::BottomRight:
      tpos.x -= t.hull.width();
      break;
    case Anchor::CenterLeft:
      tpos.y -= 0.5f * t.hull.height();
      break;
    case Anchor::Center:
      tpos -= 0.5f * glm::vec2(t.hull.width(), t.hull.height());
      break;
    case Anchor::CenterRight:
      tpos -= glm::vec2(t.hull.width(), 0.5 * t.hull.height());
      break;
    case Anchor::TopLeft:
      tpos.y -= t.hull.height();
      break;
    case Anchor::TopCenter:
      tpos -= glm::vec2(0.5f * t.hull.width(), t.hull.height());
      break;
    case Anchor::TopRight:
      tpos -= glm::vec2(t.hull.width(), t.hull.height());
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

    shader_->setUniformMatrix(pmat, "proj_mat");
    shader_->setUniformVec3(glm::vec3(t.color.r, t.color.g, t.color.b), "color");

    step = std::tuple_size<Quad>::value *  t.text.size();
    vbo_->draw(GL_TRIANGLES, sidx, step);
    sidx += step;
  }
  //if (wireframe)
  //{
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //}

  glBindTexture(GL_TEXTURE_2D, oldtex);
  glActiveTexture((GLenum)oldactivetex);
  return true;
}

void Traits3D::StandardTextEngine::clear()
{
  texts_.clear();
  coords_.clear();
}
