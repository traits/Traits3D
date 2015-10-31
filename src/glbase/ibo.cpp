#include <stdexcept>
#include "traits3d/glbase/vao.h"
#include "traits3d/glbase/ibo.h"


namespace Traits3D
{
namespace GL
{

IBO::IBO(VAO *vao)
    : vao_(vao)
{
    if (!vao_)
        throw std::domain_error(__FUNCTION__ ": IBO construction error");

    draw_type_ = GL_STATIC_DRAW;
    logGlError(); //todo temp reset for gl error flag
    glGenBuffers(1, &id_);

    if (GL_NO_ERROR != logGlError())
        throw std::domain_error(__FUNCTION__ ": IBO construction error");
}

bool IBO::bindData()
{
    if (indexmaker_.container().empty() || indexmaker_.container()[0].empty())
        return false;

    VAO::Binder vb(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    size_t size = indexmaker_.linearSize();

    if (!size_ || size_ != size || draw_type_.modified)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexMaker::IndexType) * size, nullptr, draw_type_.value);

    GLintptr offset = 0;

    for (auto const &a : indexmaker_.container())
    {
        size_t len = sizeof(IndexMaker::IndexType) * a.size();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, len, &a[0]);
        offset += len;
    }

    if (GL_NO_ERROR != logGlError())
        return false;

    draw_type_.modified = false;
    size_ = size;
    return true;
}

bool IBO::create(size_t xsize, size_t ysize, GLenum primitive_type)
{
    primitive_type_ = primitive_type;
    indexmaker_.setRestartBehavior(IndexMaker::RestartType::PrimitiveRestart, std::numeric_limits<IndexMaker::IndexType>::max());
    return indexmaker_.create(static_cast<GLuint>(xsize), static_cast<GLuint>(ysize), primitive_type);
}

bool IBO::draw()
{
    if (!bindData())
        return false;

    VAO::Binder vb(vao_);

    if (IndexMaker::RestartType::PrimitiveRestart == indexmaker_.restartType())
    {
        //todo older OpenGL (ES) versions
        #if defined(TRAITS3D_GL_IS_OPENGL_ES)
        glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
        #elif defined(TRAITS3D_GL_IS_OPENGL)
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(indexmaker_.restartPLaceholder()); //todo not available in OpenGL ES!
        #endif
    }

    const IndexMaker::IndexType *ptr = nullptr;

    for (auto const &a : indexmaker_.container())
    {
        glDrawElements(primitive_type_, static_cast<GLsizei>(a.size()), GL_UNSIGNED_INT, ptr);
        ptr += a.size();
    }

    if (IndexMaker::RestartType::PrimitiveRestart == indexmaker_.restartType())
    {
        #if defined(TRAITS3D_GL_IS_OPENGL_ES)
        glDisable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
        #elif defined(TRAITS3D_GL_IS_OPENGL)
        glDisable(GL_PRIMITIVE_RESTART);
        #endif
    }

    return true; //todo
}

void IBO::setData(Traits3D::GL::IndexMaker::LinearizedContainer const &indexes, bool primitive_restart)
{
    indexmaker_.setRestartBehavior(
        primitive_restart ? Traits3D::GL::IndexMaker::RestartType::PrimitiveRestart
        : Traits3D::GL::IndexMaker::RestartType::None
        , std::numeric_limits <IndexMaker::IndexType>::max());
    indexmaker_.setRawData(indexes);
}

} // ns
} // ns