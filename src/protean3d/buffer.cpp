#include "buffer.h"

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

bool Protean3D::GL::VAO::appendIndexVBO(std::vector<GLuint> const& data, bool dynamic /*= false*/)
{
  return appendVBO_(GL_ELEMENT_ARRAY_BUFFER, &data[0], data.size(), dynamic);
}

