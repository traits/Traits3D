#include "vbo.h"

Protean3D::GL::VBO::VBO(PrimitiveLayout const& descr) 
  : bsize_(0), description_(descr)
{
  glGenBuffers(1, &id_);
  if (GL_NO_ERROR != glGetError())
    throw std::domain_error("Protean3D: VBO construction error");
}

bool Protean3D::GL::VBO::bindAttribute(GLuint attr_location)
{
  glBindBuffer(GL_ARRAY_BUFFER, id_);

  char* ptr = nullptr;
  ptr += description_.offset;
  glVertexAttribPointer(attr_location, description_.components, description_.type, 
    GL_FALSE, description_.stride, ptr);
  if (GL_NO_ERROR != glGetError())
    return false;

  glEnableVertexAttribArray(attr_location);
  if (GL_NO_ERROR != glGetError())
    return false;

  return true;
}
