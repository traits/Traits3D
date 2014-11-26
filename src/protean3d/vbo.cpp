#include "vbo.h"

Protean3D::GL::VBO::VBO(PrimitiveLayout const& descr) 
  : bsize_(0), description_(descr)
{
  glGenBuffers(1, &id_);
  if (GL_NO_ERROR != glGetError())
    throw std::domain_error("Protean3D: VBO construction error");
}

bool Protean3D::GL::VBO::bindShader(GLuint program_id, std::string attr_name)
{
  if (attr_name.empty())
    return false;

  glBindBuffer(GL_ARRAY_BUFFER, id_);

  GLuint attrloc = glGetAttribLocation(program_id, attr_name.c_str());
  if (GL_NO_ERROR != glGetError())
    return false;

  char* ptr = nullptr;
  ptr += description_.offset;
  glVertexAttribPointer(attrloc, description_.components, description_.type, GL_FALSE, description_.stride, ptr);
  if (GL_NO_ERROR != glGetError())
    return false;

  glEnableVertexAttribArray(attrloc);
  if (GL_NO_ERROR != glGetError())
    return false;

  return true;
}
