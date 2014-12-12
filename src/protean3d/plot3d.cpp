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

  //todo enable this, we need it for correct hidden lines etc. (implement something 
  // better than glPolygonOffset 
  // e.g. https://www.opengl.org/discussion_boards/showthread.php/179958-How-to-draw-one-line-on-top-of-another-in-OpenGL-without-Z-fighting?p=1245277&viewfull=1#post1245277
  glEnable(GL_DEPTH_TEST);
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
  coordinates_object_.setProjectionMatrix(projection_matrix_);
  coordinates_object_.setModelViewMatrix(modelview_matrix_);

  data_object_.setProjectionMatrix(projection_matrix_);
  data_object_.setModelViewMatrix(modelview_matrix_);

  if (!data_object_.addPositionData(data, xsize, ysize, drawtype))
    return false;

  coordinates_object_.setHull(data_object_.hull());
  return true;
}

// todo check size against position vector[s]
bool Protean3D::Plot3D::addDataColor(std::vector<glm::vec4> const& val)
{
  return data_object_.addColor(val);
}



bool Protean3D::Plot3D::addMeshColor(glm::vec4 const& val)
{
  return data_object_.addMeshColor(val);
}

bool Protean3D::Plot3D::updatePositionData(std::vector<glm::vec3> const& data)
{
  if (!data_object_.updatePositionData(data))
    return false;

  coordinates_object_.setHull(data_object_.hull());
  return true;
}

void Protean3D::Plot3D::draw()
{
  this->setData();
  /* render the next frame */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  coordinates_object_.draw();
  data_object_.draw();
}