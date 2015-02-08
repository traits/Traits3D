#include "protean3d/glbase/vao.h"
#include "protean3d/glbase/ibo.h"


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
  if (indexmaker_.container().empty() || indexmaker_.container()[0].empty())
    return false;

  vao_->bind();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
 
  GLint oldtype;
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_USAGE, &oldtype);
  if (GL_NO_ERROR != glGetError())
    return false;

  size_t size = indexmaker_.linearSize();

  if (!size_ || size_ != size || static_cast<GLenum>(oldtype) != draw_type)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexMaker::IndexType) * size, nullptr, draw_type);

  GLintptr offset = 0;
  for (auto const& a : indexmaker_.container())
  {
    size_t len = sizeof(IndexMaker::IndexType) * a.size();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, len, &a[0]);
    offset += len;
  }

  if (GL_NO_ERROR != glGetError())
    return false;
  
  size_ = size;
  return true;
}

bool Protean3D::GL::IBO::create(size_t xsize, size_t ysize, GLenum primitive_type)
{
  primitive_type_ = primitive_type;
  return indexmaker_.create(restart_type_, xsize, ysize, primitive_type);
}

bool Protean3D::GL::IBO::draw(GLenum draw_type)
{
  if (!bindData(draw_type))
    return false;

//#if !defined PROTEAN3D_GL_IS_OPENGL_ES
//  if (IndexMaker::RestartType::PrimitiveRestart == restart_type_)
//  {
//	  glEnable(GL_PRIMITIVE_RESTART);
//	  glPrimitiveRestartIndex(std::numeric_limits<GLuint>::max()); //todo not available in OpenGL ES!
//  }
//#endif

  const IndexMaker::IndexType* ptr = nullptr;
  for (auto const& a : indexmaker_.container())
  {
    glDrawElements(primitive_type_, static_cast<GLsizei>(a.size()), GL_UNSIGNED_INT, ptr); //todo ibo indexing
    ptr +=  a.size();
  }
//#if !defined PROTEAN3D_GL_IS_OPENGL_ES
//  if (IndexMaker::RestartType::PrimitiveRestart == restart_type_)
//  {
//    glDisable(GL_PRIMITIVE_RESTART);
//  }
//#endif
  return true; //todo
}
