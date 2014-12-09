#include "globject.h"


Protean3D::GL::Object::Object()
{
}

void Protean3D::GL::Object::setProjectionMatrix(glm::mat4 const& mat)
{
  projection_matrix_p = mat;
}

void Protean3D::GL::Object::setModelViewMatrix(glm::mat4 const& mat)
{
  modelview_matrix_p = mat;
}
