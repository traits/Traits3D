#include <glm/gtc/matrix_transform.hpp>
#include "plot3d.h"


Protean3D::Plot3D::Plot3D()
{
  view_angle = 65.0f * static_cast<GLfloat>(Protean3D::PI) / 180;
  aspect_ratio = 4.0f / 3.0f;
  z_near = 1.0f;
  z_far = 100.f;

  projection_matrix_p = glm::perspective(view_angle, aspect_ratio, z_near, z_far);
  modelview_matrix_p = glm::rotate(glm::mat4(1.0f), glm::radians(-70.0f), glm::vec3(1, 0, 0));

  /* Set the camera position */
  modelview_matrix_p[3][0] = -5.0f;
  modelview_matrix_p[3][1] = -4.0f;
  modelview_matrix_p[3][2] = -7.0f;
}

Protean3D::Plot3D::~Plot3D()
{

}

void Protean3D::Plot3D::draw()
{
  this->updateData();

  //glClearColor(bgcolor_.r, bgcolor_.g, bgcolor_.b, bgcolor_.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  
  Triple beg = data_object_p->hull().minVertex;
  Triple end = data_object_p->hull().maxVertex;
  Triple center = beg + (end - beg) * 0.5;
  float radius = static_cast<float>(glm::distance(center,beg)); //todo

  modelview_matrix_p = glm::mat4(1.0f);
  //setRotation(20.0f, 0.0f, zRotation() + 1.0f);

  modelview_matrix_p = glm::rotate(modelview_matrix_p, 
    glm::radians(xRotation()-90), glm::vec3(1.0f, 0.0f, 0.0f));
  modelview_matrix_p = glm::rotate(modelview_matrix_p, 
    glm::radians(yRotation()), glm::vec3(0.0f, 1.0f, 0.0f));
  modelview_matrix_p = glm::rotate(modelview_matrix_p, 
    glm::radians(zRotation()), glm::vec3(0.0f, 0.0f, 1.0f));

  modelview_matrix_p = glm::scale(modelview_matrix_p, glm::vec3(zoom() * xScale(), zoom() * yScale(), zoom() * zScale()));
  modelview_matrix_p = glm::translate(modelview_matrix_p, glm::vec3(
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

  coordinates_object_p->setModelViewMatrix(modelview_matrix_p);
  coordinates_object_p->setProjectionMatrix(projection_matrix_p);
  coordinates_object_p->draw();
  data_object_p->setModelViewMatrix(modelview_matrix_p);
  data_object_p->setProjectionMatrix(projection_matrix_p);
  data_object_p->draw();
}

bool Protean3D::Plot3D::initializeGL()
{
  ExtGLWidget::initializeGL();
  coordinates_object_p = std::make_unique<GL::CoordinatesObject>();
  data_object_p = std::make_unique<GL::DataObject>();
  return true;
}
