#include "vbo.h"

Protean3D::GL::VBO::VBO(PrimitiveLayout const& descr) 
  : bsize_(0), description_(descr)
{
  glGenBuffers(1, &id_);
  if (GL_NO_ERROR != glGetError())
    throw std::domain_error("Protean3D: VBO construction error");
}

bool Protean3D::GL::VBO::bindShader(GLenum program_id, std::string attr_name)
{
  if (attr_name.empty())
    return false;

  GLuint attrloc = glGetAttribLocation(program_id, attr_name.c_str());
  GLenum err = glGetError();
  if (GL_INVALID_OPERATION == err)
    return false;

  char* ptr = nullptr;
  ptr += description_.offset;
  glVertexAttribPointer(attrloc, description_.components, description_.type, GL_FALSE, description_.stride, ptr);
  err = glGetError();
  if (GL_NO_ERROR != err)
    return false;

  glEnableVertexAttribArray(attrloc);
  if (GL_NO_ERROR != glGetError())
    return false;

  return true;
}
