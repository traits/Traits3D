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
  glm::mat4 m_scale = glm::scale(modelview_matrix_p, glm::vec3(xScale(), yScale(), zScale()));
  glm::mat4 m_zoom = glm::scale(modelview_matrix_p, glm::vec3(zoom()));


  // scaling/zooming influence

  std::array<float, 3> scales;
  scales[0] = xScale();
  scales[1] = yScale();
  scales[2] = zScale();

  float smax = (*std::max_element(scales.cbegin(), scales.cend()));
  //if (smax < 1)
  //  smax = 1;

  smax *= radius;

  double xrot_r = deg2rad(xRotation()+90);
  double yrot_r = deg2rad(yRotation());
  double zrot_r = deg2rad(zRotation());
  float neg_cos_xrot = -static_cast<float>(std::cos(xrot_r));

  glm::vec3 up(std::sin(yrot_r), 0, std::cos(yrot_r));
  glm::vec3 eye(
    neg_cos_xrot * std::sin(zrot_r), 
    neg_cos_xrot * std::cos(zrot_r), 
    std::sin(xrot_r));

  eye = glm::normalize(eye);

  up = glm::cross(glm::vec3(0, 0, 1), eye);
  if (up.length() < 0.03)
    up = glm::cross(glm::vec3(0, 1, 0), eye);

  //glm::vec3 X = up;
  
  up = glm::cross(eye, up);

  if (xRotation() > 90 && xRotation() <= 270)
    up = -up;

  eye = eye * smax * 7.0f;
  eye +=  glm::vec3(center);

  //up = calculateUpVector(eye, glm::vec3(center));

  glm::mat4 m_lookat = glm::lookAt(eye, glm::vec3(center), up);
  
  //glm::mat4 m_lookat = glm::lookAt(eye, glm::vec3(center), up);


  //glm::vec3 Y = up;
  //glm::vec3 Z = eye - glm::vec3(center);

  //X = glm::normalize(X);
  //Y = glm::normalize(Y);
  //Z = glm::normalize(Z);

  //m_lookat[0][0] = X.x;
  //m_lookat[1][0] = X.y;
  //m_lookat[2][0] = X.z;
  //m_lookat[3][0] = -glm::dot(X, eye);
  //m_lookat[0][1] = Y.x;
  //m_lookat[1][1] = Y.y;
  //m_lookat[2][1] = Y.z;
  //m_lookat[3][1] = -glm::dot(Y, eye);
  //m_lookat[0][2] = Z.x;
  //m_lookat[1][2] = Z.y;
  //m_lookat[2][2] = Z.z;
  //m_lookat[3][2] = -glm::dot(Z, eye);
  //m_lookat[0][3] = 0;
  //m_lookat[1][3] = 0;
  //m_lookat[2][3] = 0;
  //m_lookat[3][3] = 1.0f;


  glm::mat4 m_translate = -glm::translate(glm::mat4(1.0f), glm::vec3(center) - eye);
  m_lookat = glm::mat4(1);

  //m_lookat = rotMatrix(glm::vec3(center)-eye);


  modelview_matrix_p = m_translate * m_zoom * m_scale * m_lookat; // lookAt first

  float l(-radius), r(radius), b(-radius), t(radius), n(3 * smax * zoom()), f(8 * smax * zoom());

  l -= xViewportShift() * 2 * radius;
  r -= xViewportShift() * 2 * radius;
  b -= yViewportShift() * 2 * radius;
  t -= yViewportShift() * 2 * radius;
  
  matrices_p.setModelView(modelview_matrix_p);
  matrices_p.setProjection(ortho(), l, r, b, t, n, f);

  coordinates_p->draw(matrices_p);
  data_object_p->draw(matrices_p);
  
  //Axis aux_a(center, Triple(eye)-center);
  //aux_a.setLimits(0, c_dist);
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
