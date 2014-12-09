#include <glm/gtc/matrix_transform.hpp>
#include "plot3d.h"


Protean3D::Plot3D::Plot3D()
{
  view_angle = 65.0f * static_cast<GLfloat>(Protean3D::PI) / 180;
  aspect_ratio = 4.0f / 3.0f;
  z_near = 1.0f;
  z_far = 100.f;

  projection_matrix_ = glm::perspective(view_angle, aspect_ratio, z_near, z_far);
  modelview_matrix_ = glm::rotate(glm::mat4(1.0f), glm::radians(-70.0f), glm::vec3(1, 0, 0));

  /* Set the camera position */
  modelview_matrix_[3][0] = -5.0f;
  modelview_matrix_[3][1] = -4.0f;
  modelview_matrix_[3][2] = -7.0f;
}

Protean3D::Plot3D::~Plot3D()
{

}


/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
* the specified program object
*/
bool Protean3D::Plot3D::addPositionData(std::vector<glm::vec3> const& data,
  size_t xsize, size_t ysize, GLenum drawtype /*= GL_STATIC_DRAW*/) 
{
  data_object_.setProjectionMatrix(projection_matrix_);
  data_object_.setModelViewMatrix(modelview_matrix_);

  return data_object_.addPositionData(data, xsize, ysize, drawtype);
}

// todo check size against position vector[s]
bool Protean3D::Plot3D::addColorData(std::vector<glm::vec4> const& data)
{
  return data_object_.addColorData(data);
}

bool Protean3D::Plot3D::updatePositionData(std::vector<glm::vec3> const& data)
{
  return data_object_.updatePositionData(data);
}

void Protean3D::Plot3D::draw()
{
  this->setData();
  /* render the next frame */
  glClear(GL_COLOR_BUFFER_BIT);

  data_object_.draw();
}