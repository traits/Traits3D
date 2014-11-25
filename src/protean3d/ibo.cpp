#include "indexmaker.h"
#include "IBO.h"


Protean3D::GL::IBO::IBO() : size_(0)
{
  glGenBuffers(1, &id_);
  if (GL_NO_ERROR != glGetError())
    throw std::domain_error("Protean3D: IBO construction error");
}

bool Protean3D::GL::IBO::bindData(GLenum drawtype)
{
  if (indexes_.empty())
    return false;

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
 
  GLint oldtype;
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_USAGE, &oldtype);
  if (GL_NO_ERROR != glGetError())
    return false;

  size_t size = indexes_.size();
  if (!size_ || size_ != size || static_cast<GLenum>(oldtype) != drawtype)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * size, size ? &indexes_[0] : nullptr, drawtype);
  else
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLuint) * size, size ? &indexes_[0] : nullptr);


  if (GL_NO_ERROR != glGetError())
    return false;
  
  size_ = size;
  return true;
}

bool Protean3D::GL::IBO::create(size_t xsize, size_t ysize, GLenum primitive_type)
{
  IndexMaker im;
  return im.create(indexes_, xsize, ysize, primitive_type);
}
