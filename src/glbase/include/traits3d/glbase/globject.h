#pragma once

#include "traits3d/glbase/vao.h"

namespace Traits3D
{
namespace GL
{
class Shader;
class Transformation;

class Object
{
public:
    Object() = default;
    virtual ~Object() = default;
    virtual void draw(Transformation const &matrices) = 0;
    //! Sets projection/mv/normal matrices for shader s;
    bool setStdMatrices(Shader &s, Transformation const &t);

protected:
    GL::VAO vao_p;
};
} // ns
} // ns
