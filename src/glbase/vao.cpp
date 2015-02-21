#include "traits3d/glbase/vao.h"

Traits3D::GL::VAO::VAO()
{
  glGenVertexArrays(1, &id_);
}


Traits3D::GL::VAO::~VAO()
{
  //if (GL_TRUE == glIsVertexArray(id_))
  //  glDeleteVertexArrays(1, &id_);
}

void Traits3D::GL::VAO::bind()
{
  GLuint val;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)(&val));
  if (val != id_)
    glBindVertexArray(id_);
}

void Traits3D::GL::VAO::unbind()
{
  GLuint val;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)(&val));
  if (val == id_)
    glBindVertexArray(0);
}
