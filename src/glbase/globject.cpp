#include "glb/shader_std.h"
#include "glb/shader.h"
#include "glb/transformation.h"
#include "glb/globject.h"

namespace glb
{
bool Object::setStdMatrices(Shader &s, Transformation const &t)
{
    return
        s.setUniformMatrix(t.proj(), shadercode::Var::proj_matrix)
        &&
        s.setUniformMatrix(t.mv(), shadercode::Var::mv_matrix)
        &&
        s.setUniformMatrix(t.normalMatrix(), shadercode::Var::normal_matrix);
}
} // ns

