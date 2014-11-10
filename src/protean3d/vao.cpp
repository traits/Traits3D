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

bool Protean3D::GL::VAO::appendIBO(std::vector<GLuint> const& data, bool dynamic /*= false*/)
{
  //static_assert(std::is_same<PRIMITIVE, GLfloat>::value, "Incorrect buffer type!");
  IBO buffer;
  if (buffer.create(data, dynamic))
  {
    ibos_.push_back(buffer);
    return true;
  }
  return false;
}
