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

bool Protean3D::GL::VAO::appendIBO(size_t xsize, size_t ysize, GLenum primitive_type)
{
  //static_assert(std::is_same<PRIMITIVE, GLfloat>::value, "Incorrect buffer type!");
  IBO buffer;
  if (buffer.create(xsize, ysize, primitive_type))
  {
    ibos_.push_back(buffer);
    return true;
  }
  return false;
}

bool Protean3D::GL::VAO::bindIBO(size_t idx, GLenum draw_type /*= GL_STATIC_DRAW*/)
{
  return (idx < ibos_.size() && ibos_[idx].bindData(draw_type));
}

bool Protean3D::GL::VAO::bindShader(size_t idx, GLuint program, const char* attr_name)
{
  return (idx < vbos_.size() && vbos_[idx].bindShader(program, attr_name));
}
