#include "vbo.h"

Protean3D::GL::VBO::VBO(VAO* vao) 
  :vao_(vao)
{
  if (!vao_)
    throw std::domain_error("Protean3D: VBO construction error");

  glGenBuffers(1, &id_);
  if (GL_NO_ERROR != glGetError())
    throw std::domain_error("Protean3D: VBO construction error");
}

bool Protean3D::GL::VBO::bindAttribute(GLuint attr_location)
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

bool Protean3D::GL::VBO::draw(GLenum primitive_type, size_t first, size_t count)
{
  GLuint glfirst = static_cast<GLuint> (first * primitive_size_);
  GLsizei glcount = static_cast<GLuint> (count * primitive_size_);

  if (glfirst + glcount > bsize_)
    return false;

  glDrawArrays(primitive_type, glfirst, glcount); 

  GLenum err = glGetError();

  return GL_NO_ERROR == err;
}

bool Protean3D::GL::VBO::setData(std::vector<glm::vec3> const& data, 
  bool setdrawtype/* = false*/, GLenum drawtype /*= GL_STATIC_DRAW*/)
{
  if (!layout_.match(Layout(3, GL_FLOAT, 0, 0)))
    return false;

  return setData<glm::vec3>(data, setdrawtype, drawtype);
}

bool Protean3D::GL::VBO::setData(std::vector<glm::vec4> const& data, 
  bool setdrawtype/* = false*/, GLenum drawtype /*= GL_STATIC_DRAW*/)
{
  if (!layout_.match(Layout(4, GL_FLOAT, 0, 0)))
    return false;

  return setData<glm::vec4>(data, setdrawtype, drawtype);
}
