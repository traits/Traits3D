#include <stdexcept>
#include "glb/vao.h"
#include "glb/vbo.h"

namespace glb
{

VBO::VBO(VAO *vao, char layout_components)
    : vao_(vao)
{
    if (!vao_)
        throw std::domain_error(__FUNCTION__ ": VBO construction error");

    bsize_ = 0;
    primitive_size_ = 1;
    draw_type_ = GL_STATIC_DRAW;
    logGlError(); //todo temp reset for gl error flag
    glGenBuffers(1, &id_);

    if (GL_NO_ERROR != logGlError())
        throw std::domain_error(__FUNCTION__": VBO construction error");

    setLayout(Layout(layout_components));
    draw_type_ = GL_STATIC_DRAW;
}

bool VBO::bindAttribute(GLuint program_id, std::string const &name)
{
    if (name.empty())
        return false;

    GLuint attr_location = glGetAttribLocation(program_id, name.c_str());

    if (GL_NO_ERROR != logGlError())
        return false;

    VAO::Binder vb(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    char *ptr = nullptr;
    ptr += layout_.offset;
    glVertexAttribPointer(attr_location, layout_.components, layout_.type,
                          GL_FALSE, layout_.stride, ptr);

    if (GL_NO_ERROR != logGlError())
        return false;

    glEnableVertexAttribArray(attr_location);

    if (GL_NO_ERROR != logGlError())
        return false;

    return true;
}

bool VBO::unbindAttribute(GLuint program_id, std::string const &name)
{
    if (name.empty())
        return false;

    GLuint attr_location = glGetAttribLocation(program_id, name.c_str());

    if (GL_NO_ERROR != logGlError())
        return false;

    VAO::Binder vb(vao_);
    glDisableVertexAttribArray(attr_location);

    if (GL_NO_ERROR != logGlError())
        return false;

    return true;
}

/**
 \param primitive_type Type of the primitive (GL_TRIANGLE_STRIP etc.).
 \param first          Index to the first element to draw. An element means an entity,
 set by the corresponding overloaded setData call (glm::vec4 etc.)
 \param count          Number of elements to draw.

 \return true if it succeeds, false if it fails.
 */
bool VBO::draw(GLenum primitive_type, size_t first, size_t count)
{
    if ((first + count)*primitive_size_ > bsize_)
        return false;

    VAO::Binder vb(vao_);
    glDrawArrays(primitive_type, static_cast<GLint>(first), static_cast<GLsizei>(count));
    return GL_NO_ERROR == logGlError();
}

bool VBO::draw(GLenum primitive_type)
{
    return draw(primitive_type, 0, bsize_ / primitive_size_);
}

bool VBO::setData(std::vector<glm::vec3> const &data)
{
    if (!layout_.match(Layout(3, GL_FLOAT, 0, 0)))
        return false;

    return setData<glm::vec3>(data);
}

bool VBO::setData(std::vector<glm::vec4> const &data)
{
    if (!layout_.match(Layout(4, GL_FLOAT, 0, 0)))
        return false;

    return setData<glm::vec4>(data);
}

} // ns
