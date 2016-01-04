#pragma once

#include <vector>
#include "traits3d/types.h"
#include "glb/glhelper.h"
#include "glb/indexmaker.h"

namespace glb
{
class VAO;

//! Index Buffer Objects
class IBO
{
public:
    explicit IBO(VAO *vao);
    virtual ~IBO() = default;
    //GLuint id() const { return id_; } //!< IBO index
    //size_t size() const { return size_; } //! buffer size in sizeof(GLuint)
    //GLenum primitiveType() const { return primitive_type_; } //! GL_TRIANGLE_STRIP etc.

    bool create(size_t xsize, size_t ysize, GLenum primitive_type);
    bool draw();
    void setDrawType(GLenum val)
    {
        if (val != draw_type_.value) draw_type_.value = val;
    }
    bool drawTypeModified() const
    {
        return draw_type_.modified;
    }
    void setData(IndexMaker::LinearizedContainer const &indexes, bool primitive_restart);

private:
    GLuint id_ = 0;
    size_t size_ = 0; //buffer size
    IndexMaker indexmaker_;
    GLenum primitive_type_ = GL_TRIANGLE_STRIP;
    VAO *vao_;
    traits3d::StateEntity<GLenum> draw_type_; // GL_STATIC_DRAW or GL_DYNAMIC_DRAW

    bool bindData();
};
} // ns

