#include "vbo.h"

Protean3D::GL::VBO::VBO(PrimitiveLayout const& descr) 
  : description_(descr)
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

bool Protean3D::GL::VBO::draw(GLenum primitive_type, size_t first, size_t count)
{
  GLuint glfirst = static_cast<GLuint> (first * primitive_size_);
  GLsizei glcount = static_cast<GLuint> (count * primitive_size_);

  if (glfirst + glcount > bsize_)
    return false;

  glDrawArrays(primitive_type, glfirst, glcount); 

  GLenum err = glGetError();

  return GL_NO_ERROR == err;
}
