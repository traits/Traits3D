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

  float radius = static_cast<float>(glm::distance(center,beg));

  if (isZero(radius))
    return;

  // mv transformation

  glm::mat4 modelview_matrix_p = glm::mat4(1.0f);
  glm::mat4 m_scale = glm::scale(modelview_matrix_p, glm::vec3(xScale(), yScale(), zScale()));
  glm::mat4 m_zoom = glm::scale(modelview_matrix_p, glm::vec3(zoom()));


  // scaling/zooming influence

  std::array<float, 3> scales;
  scales[0] = xScale() * zoom();
  scales[1] = yScale() * zoom();
  scales[2] = zScale() * zoom();

  float smax = radius * (*std::max_element(scales.cbegin(), scales.cend()));


  // rotation 
  
  float xrot_r = static_cast<float>(xRotation() - PI / 2);
  float yrot_r = static_cast<float>(yRotation());
  float zrot_r = static_cast<float>(zRotation());
  
  glm::mat4 m_rotate = glm::rotate(glm::mat4(1.0f), xrot_r, glm::vec3(1, 0, 0));
  m_rotate = glm::rotate(m_rotate, yrot_r, glm::vec3(0, 1, 0));
  m_rotate = glm::rotate(m_rotate, zrot_r, glm::vec3(0, 0, 1));

  // 'lookat'
  glm::vec3 eye = glm::vec3(0, 0, smax * 7.0f) + glm::vec3(center);
  glm::mat4 m_translate = glm::translate(glm::mat4(1.0f), glm::vec3(center) - eye);
  
  // initial model centering
  glm::mat4 m_translate2center = glm::translate(glm::mat4(1.0f), -glm::vec3(center));
  
  // completed MV matrix
  modelview_matrix_p = m_translate * m_zoom * m_scale * m_rotate * m_translate2center; 

  float l(-radius), r(radius), b(-radius), t(radius), n(3 * smax ), f(8 * smax);

  l -= xViewportShift() * 2 * radius;
  r -= xViewportShift() * 2 * radius;
  b -= yViewportShift() * 2 * radius;
  t -= yViewportShift() * 2 * radius;
  
  matrices_p.setModelView(modelview_matrix_p);
  matrices_p.setProjection(ortho(), l, r, b, t, n, f);

  coordinates_p->draw(matrices_p);
  data_object_p->draw(matrices_p);
  
  //Axis aux_a(center, Triple(eye)-center);
  //aux_a.setLimits(0, 0);
  //aux_a.initializeGL();
  ////aux_a.showNumbers(true);
  //aux_a.setAutoScale(false);
  //aux_a.setMajors(1);
  //aux_a.setColor(Color(1,0,0,1));
  //aux_a.draw(matrices_p);


  //todo
  glm::ivec4 vp = GL::viewPort();

  setTitle(title_);
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

/*!
Set style of coordinate system
*/
void Traits3D::Plot3D::setCoordinateStyle(Traits3D::COORDINATESTYLE st)
{
  coordinates_p->setStyle(st);
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
