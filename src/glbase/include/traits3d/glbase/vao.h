#pragma once

#include <vector>
#include "traits3d/glbase/glhelper.h"

namespace traits3d
{
namespace gl
{

//! Unifies buffer handling the VAO way
class VAO
{
public:
    VAO();
    virtual ~VAO();

    //! RAII VAO binding for IBO/VBO internal usage
    class Binder
    {
    private:
        VAO *vao_;

    public:
        explicit Binder(VAO *vao)
            : vao_(vao)
        {
            if (vao_)
                vao_->bind();
        }
        ~Binder()
        {
            if (vao_)
                vao_->unbind();
        }
    };

private:
    GLuint id_ = 0;
    void bind();
    void unbind();
};

}
} // ns