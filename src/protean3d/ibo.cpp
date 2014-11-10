#include "IBO.h"


bool Protean3D::GL::IBO::create(std::vector<GLuint> const& data, GLenum drawtype /*= GL_STATIC_DRAW*/)
{
  glGenBuffers(1, &id_);
  if (GL_INVALID_VALUE == glGetError())
    return false;

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
  size_t bsize = sizeof(GLuint) * data.size();

  if (!bsize_ || bsize_ != bsize)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bsize, bsize ? &data[0] : nullptr, draw_type_);
  else
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, bsize, bsize ? &data[0] : nullptr);

  bsize_ = bsize;

  GLenum err = glGetError();
  switch (err)
  {
  case GL_INVALID_ENUM:
  case GL_INVALID_OPERATION:
  case GL_OUT_OF_MEMORY:
    return false;
  default:
    return true;
  }
}
