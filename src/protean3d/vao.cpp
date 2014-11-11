#include "vao.h"

Protean3D::GL::VAO::VAO()
  :idx_(0)
{
  glGenVertexArrays(1, &idx_);
}


Protean3D::GL::VAO::~VAO()
{
  if (GL_TRUE == glIsVertexArray(idx_))
    glDeleteVertexArrays(1, &idx_);
}

size_t Protean3D::GL::VAO::appendIBO(std::vector<GLuint> const& data, GLenum draw_type /*= GL_STATIC_DRAW*/)
{
  //static_assert(std::is_same<PRIMITIVE, GLfloat>::value, "Incorrect buffer type!");
  IBO buffer;
  if (buffer.create(data, draw_type))
  {
    ibos_.push_back(buffer);
    return ibos_.size()-1;
  }
  return std::numeric_limits<size_t>::max();
}
