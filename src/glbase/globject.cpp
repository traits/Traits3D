#include "traits3d/glbase/shader_std.h"
#include "traits3d/glbase/shader.h"
#include "traits3d/glbase/transformation.h"
#include "traits3d/glbase/globject.h"

namespace traits3d
{
namespace gl
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
} // ns

