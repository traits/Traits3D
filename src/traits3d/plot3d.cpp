#include <glm/gtc/matrix_transform.hpp>
#include "traits3d/helper.h"
#include "traits3d/textengine/textengine_std.h"
#include "traits3d/plot3d.h"


Traits3D::Plot3D::Plot3D()
{
  text_engine_p = std::make_shared<StandardTextEngine>();
  coordinates_p = std::make_shared<Coordinates>();
}

Traits3D::Plot3D::~Plot3D()
{
}

void Traits3D::Plot3D::draw()
{
  if (!isInitialized())
    return;

  this->updateData();

  glClearColor(bgcolor_.r, bgcolor_.g, bgcolor_.b, bgcolor_.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Triple beg = data_object_p->hull().minVertex;
  Triple end = data_object_p->hull().maxVertex;
  Triple center = beg + (end - beg) * 0.5;
  float radius = static_cast<float>(glm::distance(center,beg)); //todo

  if (isZero(radius))
    return;

  // mv transformation

  glm::mat4 modelview_matrix_p = glm::mat4(1.0f);
  
  glm::mat4 m_rot = glm::rotate(modelview_matrix_p, glm::radians(xRotation() - 90), glm::vec3(1.0f, 0.0f, 0.0f))
    * glm::rotate(modelview_matrix_p, glm::radians(yRotation()), glm::vec3(0.0f, 1.0f, 0.0f))
    * glm::rotate(modelview_matrix_p, glm::radians(zRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
  
  glm::mat4 m_scale = glm::scale(modelview_matrix_p, zoom() * glm::vec3(xScale(), yScale(), zScale()));
  
  glm::mat4 m_translate = glm::translate(modelview_matrix_p, glm::vec3(
    xShift() - static_cast<float>(center.x),
    yShift() - static_cast<float>(center.y),
    zShift() - static_cast<float>(center.z)
    ));

  modelview_matrix_p *= m_rot * m_scale * m_translate;


  // scaling/zooming influence

  glm::mat4 Inverse = glm::inverse(modelview_matrix_p); //todo optimize

  std::array<float, 3> scales;
  scales[0] = xScale();
  scales[1] = yScale();
  scales[2] = zScale();

  float smax = radius * zoom() * (*std::max_element(scales.cbegin(), scales.cend()));

  // find ray along current camera-center line of sight for setting back the camera 
  //glm::vec4 bv = Inverse * glm::vec4(0, 0, 0, 1); // unit vector of original camera viewing direction (towards negative z direction)
  //glm::vec4 cv = Inverse * glm::vec4(0, 0, 1, 1); // ... 2nd defining point
  //glm::vec4 a = radius * glm::normalize(cv - bv);
  
  glm::vec3 cam_shift = -7.0f * radius * glm::vec3(
    glm::normalize(Inverse * (glm::vec4(0, 0, 1, 0)))
    );

  modelview_matrix_p = glm::translate(modelview_matrix_p, cam_shift);
  float c_dist = static_cast<float>(glm::length(cam_shift)); //todo

  float l(-1), r(1), b(-1), t(1), n(1), f(100);

  //setOrtho(false);
  if (beg != end)
  {
    l = -radius;
    r = radius;
    b = -radius;
    t = radius;
    n = 3 * smax;
    f = 8 * smax;
  }

  l -= xViewportShift() * 2 * radius;
  r -= xViewportShift() * 2 * radius;
  b -= yViewportShift() * 2 * radius;
  t -= yViewportShift() * 2 * radius;
 
  glm::mat4 projection_matrix_p = ortho() ? glm::ortho(l, r, b, t, n, f) : glm::frustum(l, r, b, t, n, f);
  matrices_p.set(projection_matrix_p, modelview_matrix_p, ortho(), l, r, b, t, n, f);

  coordinates_p->draw(matrices_p);
  data_object_p->draw(matrices_p);

  //todo
  glm::ivec4 vp = GL::viewPort();


  std::string title("r: ");
  title += text_engine_p->double2text(radius)
    + ", zoom: "
    + text_engine_p->double2text(zoom())
    + ", xs: "
    + text_engine_p->double2text(xScale())
    + ", ys: "
    + text_engine_p->double2text(yScale())
    + ", zs: "
    + text_engine_p->double2text(zScale())
    +", n: "
    + text_engine_p->double2text(n)
    + ", f: "
    + text_engine_p->double2text(f)
  +", cdist: "
    + text_engine_p->double2text(c_dist);

  setTitle(title);
  std::vector<TextEngine::Position> positions(1);
  positions[0] = TextEngine::Position(
                   TupleF((vp[2] - vp[0]) / 2, vp[3] - vp[1]-10),
                   TextEngine::Anchor::TopCenter);
  std::vector<Color> colors(1, title_color_);
  text_engine_p->draw(positions, colors);
}

void Traits3D::Plot3D::setBackgroundColor(Color const& val)
{
  bgcolor_ = val;
}

bool Traits3D::Plot3D::initializeGL()
{
  if (
    !ExtGLWidget::initializeGL()
    || !text_engine_p->initializeGL()
    || !coordinates_p->initializeGL()

  )
  {
    gl_is_initialized_p = false;
    return false;
  }
  setTitle("Traits3D Plot");
  setTitleColor(Color(0.9f, 0, 0.3f, 1.0f));
  gl_is_initialized_p = true;
  return true;
}

void Traits3D::Plot3D::setTitle(std::string const& val)
{
  if (text_engine_p->setTexts(std::vector<std::string>(1, val), std::vector<FontInfo>(1, FontInfo("OpenSans Italic", 24))))
    title_ = val;
}

void Traits3D::Plot3D::setTitleColor(Traits3D::Color const& val)
{
  title_color_ = val;
}
