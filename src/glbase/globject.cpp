#include "traits3d/glbase/shader_std.h"
#include "traits3d/glbase/shader.h"
#include "traits3d/glbase/transformation.h"
#include "traits3d/glbase/globject.h"

bool Traits3D::GL::Object::setStdMatrices(Shader &s, Transformation const &t)
{
    return
        s.setUniformMatrix(t.proj(), ShaderCode::Var::proj_matrix)
        &&
        s.setUniformMatrix(t.mv(), ShaderCode::Var::mv_matrix)
        &&
        s.setUniformMatrix(t.normalMatrix(), ShaderCode::Var::normal_matrix);
}
