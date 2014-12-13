#include "vao.h"

Protean3D::GL::VAO::VAO()
{
  glGenVertexArrays(1, &id_);
}


Protean3D::GL::VAO::~VAO()
{
  if (GL_TRUE == glIsVertexArray(id_))
    glDeleteVertexArrays(1, &id_);
}

bool Protean3D::GL::VAO::appendIBO(size_t xsize, size_t ysize, GLenum primitive_type)
{
  bind();
  //static_assert(std::is_same<PRIMITIVE, GLfloat>::value, "Incorrect buffer type!");
  IBO buffer;
  if (buffer.create(xsize, ysize, primitive_type))
  {
    ibos_.push_back(buffer);
    return true;
  }
  return false;
}

bool Protean3D::GL::VAO::drawIBO(size_t idx, GLenum draw_type)
{
  bind();
  return (idx < ibos_.size() && ibos_[idx].bindData(draw_type) && ibos_[idx].draw());
}

void Protean3D::GL::VAO::bind()
{
  GLuint val;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)(&val));
  if (val != id_)
    glBindVertexArray(id_);
}

void Protean3D::GL::VAO::unbind()
{
  GLuint val;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)(&val));
  if (val == id_)
    glBindVertexArray(0);
}
