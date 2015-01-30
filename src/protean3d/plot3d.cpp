#include <glm/gtc/matrix_transform.hpp>
#include "protean3d/textengine/textengine_std.h"
#include "protean3d/plot3d.h"


Protean3D::Plot3D::Plot3D()
{
  text_engine_p = std::make_shared<StandardTextEngine>();
  coordinates_p = std::make_shared<Coordinates>();
}

Protean3D::Plot3D::~Plot3D()
{

}

void Protean3D::Plot3D::draw()
{
  this->updateData();

  glClearColor(bgcolor_.r, bgcolor_.g, bgcolor_.b, bgcolor_.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Triple beg = data_object_p->hull().minVertex;
  Triple end = data_object_p->hull().maxVertex;
  Triple center = beg + (end - beg) * 0.5;
  float radius = static_cast<float>(glm::distance(center,beg)); //todo

  modelview_matrix_p = glm::mat4(1.0f);

  modelview_matrix_p =
    modelview_matrix_p
    * glm::rotate(modelview_matrix_p, glm::radians(xRotation() - 90), glm::vec3(1.0f, 0.0f, 0.0f))
    * glm::rotate(modelview_matrix_p, glm::radians(yRotation()), glm::vec3(0.0f, 1.0f, 0.0f))
    * glm::rotate(modelview_matrix_p, glm::radians(zRotation()), glm::vec3(0.0f, 0.0f, 1.0f))
    * glm::scale(modelview_matrix_p, glm::vec3(zoom() * xScale(), zoom() * yScale(), zoom() * zScale()))
    * glm::translate(modelview_matrix_p, glm::vec3(
        xShift() - static_cast<float>(center.x),
        yShift() - static_cast<float>(center.y),
        zShift() - static_cast<float>(center.z)));

  //setOrtho(false);
  if (beg != end)
  {
    if (ortho())
      projection_matrix_p = glm::ortho(-radius, +radius, -radius, +radius, 0.1f * radius, 40 * radius);
    else
      projection_matrix_p = glm::frustum(-radius, +radius, -radius, +radius, 5 * radius, 400 * radius);
  }
  else
  {
    if (ortho())
      projection_matrix_p = glm::ortho(-1.0, 1.0, -1.0, 1.0, 10.0, 100.0);
    else
      projection_matrix_p = glm::frustum(-1.0, 1.0, -1.0, 1.0, 10.0, 100.0);
  }

  projection_matrix_p = glm::translate(projection_matrix_p,
    glm::vec3(xViewportShift() * 2 * radius, yViewportShift() * 2 * radius, -7 * radius));

  coordinates_p->draw(projection_matrix_p, modelview_matrix_p);
  data_object_p->draw(projection_matrix_p, modelview_matrix_p);

  //todo
  glm::ivec4 vp = GL::viewPort();

  std::vector<TextEngine::Position> positions(1);
  positions[0] = TextEngine::Position(
    TupleF((vp[2] - vp[0]) / 2, vp[3] - vp[1]-10),
    TextEngine::Anchor::TopCenter);
  text_engine_p->drawText(positions);
}

void Protean3D::Plot3D::setBackgroundColor(Color val)
{
  bgcolor_ = val;
}

bool Protean3D::Plot3D::initializeGL()
{
  if (!ExtGLWidget::initializeGL())
    return false;
  
  if (!text_engine_p->initializeGL())
    return false;

  if (!coordinates_p->initializeGL())
    return false;
  
  setTitle("Protean3D Plot");
  return true;
}

void Protean3D::Plot3D::setTitle(std::string const& val)
{
  title_ = val;
  text_engine_p->setText(title_);
  text_engine_p->setColor(Color(0.9f, 0, 0.3f, 0.0f));
}
