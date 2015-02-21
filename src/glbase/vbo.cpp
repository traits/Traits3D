#include <stdexcept>
#include "traits3d/glbase/vao.h"
#include "traits3d/glbase/vbo.h"

Traits3D::GL::VBO::VBO(VAO* vao) 
  :vao_(vao)
{
  if (!vao_)
    throw std::domain_error("Traits3D: VBO construction error");

  glGetError(); //todo temp reset for gl error flag
  glGenBuffers(1, &id_);
  if (GL_NO_ERROR != glGetError())
    throw std::domain_error("Traits3D: VBO construction error");
}

bool Traits3D::GL::VBO::bindAttribute(GLuint attr_location)
{
  vao_->bind();
  glBindBuffer(GL_ARRAY_BUFFER, id_);

  char* ptr = nullptr;
  ptr += layout_.offset;
  glVertexAttribPointer(attr_location, layout_.components, layout_.type, 
    GL_FALSE, layout_.stride, ptr);
  if (GL_NO_ERROR != glGetError())
    return false;

  glEnableVertexAttribArray(attr_location);
  if (GL_NO_ERROR != glGetError())
    return false;

  return true;
}

/**
 \param primitive_type Type of the primitive (GL_TRIANGLE_STRIP etc.).
 \param first          Index to the first element to draw. An element means an entities, 
                       set by the corresponding overloaded setData call (glm::vec4 etc.)
 \param count          Number of elements to draw. 

 \return true if it succeeds, false if it fails.
 */
bool Traits3D::GL::VBO::draw(GLenum primitive_type, size_t first, size_t count)
{
  if ((first + count)*primitive_size_ > bsize_)
    return false;

  glDrawArrays(primitive_type, static_cast<GLint>(first), static_cast<GLsizei>(count));

  GLenum err = glGetError();

  return GL_NO_ERROR == err;
}

bool Traits3D::GL::VBO::draw(GLenum primitive_type)
{
  return draw(primitive_type, 0, bsize_ / primitive_size_);
}

bool Traits3D::GL::VBO::setData(std::vector<glm::vec3> const& data, GLenum drawtype /*= GL_STATIC_DRAW*/)
{
  if (!layout_.match(Layout(3, GL_FLOAT, 0, 0)))
    return false;

  return setData<glm::vec3>(data, drawtype);
}

bool Traits3D::GL::VBO::setData(std::vector<glm::vec4> const& data, GLenum drawtype /*= GL_STATIC_DRAW*/)
{
  if (!layout_.match(Layout(4, GL_FLOAT, 0, 0)))
    return false;

  return setData<glm::vec4>(data, drawtype);
}
