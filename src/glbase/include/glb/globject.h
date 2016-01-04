#pragma once

#include "glb/vao.h"

namespace glb
{
class Shader;
class Transformation;

class Object
{
public:
    Object() {}
    virtual ~Object() {}
    virtual void draw(Transformation const &matrices) = 0;
    //! Sets projection/mv/normal matrices for shader s;
    bool setStdMatrices(Shader &s, Transformation const &t);

protected:
    VAO vao_p;
};
} // ns
