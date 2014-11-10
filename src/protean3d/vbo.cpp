#include "vbo.h"

bool Protean3D::GL::VBO::create(PrimitiveLayout const& descr, GLenum drawtype /* = GL_STATIC_DRAW */)
{
  glGenBuffers(1, &id_);
  if (GL_INVALID_VALUE == glGetError())
    return false;

  description_ = descr;
  draw_type_ = drawtype;

  return true;
}
