#include "IBO.h"


Protean3D::GL::IBO::IBO(VAO* vao)
  :vao_(vao)
{
  if (!vao_)
    throw std::domain_error("Protean3D: IBO construction error");
  GLenum err = glGetError(); //todo temp reset for gl error flag
  glGenBuffers(1, &id_);
  if (GL_NO_ERROR != glGetError())
    throw std::domain_error("Protean3D: IBO construction error");
}

bool Protean3D::GL::IBO::bindData(GLenum draw_type)
{
  if (indexes_.empty())
    return false;

  vao_->bind();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
 
  GLint oldtype;
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_USAGE, &oldtype);
  if (GL_NO_ERROR != glGetError())
    return false;

  size_t size = indexes_.size();
  if (!size_ || size_ != size || static_cast<GLenum>(oldtype) != draw_type)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * size, size ? &indexes_[0] : nullptr, draw_type);
  else
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLuint) * size, size ? &indexes_[0] : nullptr);


  if (GL_NO_ERROR != glGetError())
    return false;
  
  size_ = size;
  return true;
}

bool Protean3D::GL::IBO::create(size_t xsize, size_t ysize, GLenum primitive_type)
{
  primitive_type_ = primitive_type;
  return indexmaker_.create(indexes_, restart_type_, xsize, ysize, primitive_type);
}

bool Protean3D::GL::IBO::draw(GLenum draw_type)
{
  if (!bindData(draw_type))
    return false;

  if (IndexMaker::RestartType::PrimitiveRestart == restart_type_)
  {
	  glEnable(GL_PRIMITIVE_RESTART);
	  glPrimitiveRestartIndex(std::numeric_limits<GLuint>::max()); //todo not available in OpenGL ES!
  }
  
  glDrawElements(primitive_type_, size_, GL_UNSIGNED_INT, 0); //todo ibo indexing
  
  if (IndexMaker::RestartType::PrimitiveRestart == restart_type_)
  {
    glDisable(GL_PRIMITIVE_RESTART);
  }    
    
  return true; //todo
}
