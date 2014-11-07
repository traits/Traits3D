#include "IBO.h"

bool Protean3D::GL::IBO::create_(GLuint const* data, size_t dsize, bool dynamic /*= false*/)
{
  glGenBuffers(1, &id_);
  if (GL_INVALID_VALUE == glGetError())
    return false;

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * dsize, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
  GLenum err = glGetError();

  switch (err)
  {
  case GL_INVALID_OPERATION:
  case GL_OUT_OF_MEMORY:
    return false;
  default:
    return true;
  }
}

bool Protean3D::GL::IBO::create(std::vector<GLuint> const& data, bool dynamic /*= false*/)
{
  return create_(&data[0], data.size(), dynamic);
}
