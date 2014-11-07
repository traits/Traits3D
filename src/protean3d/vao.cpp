#include "vao.h"

Protean3D::GL::VAO::VAO()
  :vao_(0)
{
  glGenVertexArrays(1, &vao_);
}


Protean3D::GL::VAO::~VAO()
{
  if (GL_TRUE == glIsVertexArray(vao_))
    glDeleteVertexArrays(1, &vao_);
}
