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

  //todo enable this, we need it for correct hidden lines etc. (implement something 
  // better than glPolygonOffset 
  // e.g. https://www.opengl.org/discussion_boards/showthread.php/179958-How-to-draw-one-line-on-top-of-another-in-OpenGL-without-Z-fighting?p=1245277&viewfull=1#post1245277
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glEnable(GL_LINE_SMOOTH);
  //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

Protean3D::Plot3D::~Plot3D()
{

}

void Protean3D::Plot3D::draw()
{
  this->setData();

  /* render the next frame */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  coordinates_object_p.draw();
  data_object_p.draw();
}
