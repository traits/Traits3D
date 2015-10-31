#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/matrix_inverse.hpp>
#include "traits3d/glbase/transformation.h"

namespace traits3d
{
namespace gl
{

Transformation::Transformation()
{
    // dummy
}

/**
 \param mv The model-view matrix to set
 */
void Transformation::setModelView(glm::mat4 const &mv)
{
    mv_ = mv;
}

/**
\param n  The normal transformation matrix to set (mat3(mv)^-1^T)
*/
void Transformation::setNormal(glm::mat3 const &n)
{
    normal_mat_ = n;
}

/**
\param n  matrix, transforming light positions invariant to model rotations in world space
*/
void Transformation::setLight(glm::mat4 const &l)
{
    light_mat_ = l;
}

void Transformation::setProjection(glm::mat4 const &proj)
{
    proj_ = proj;
}

void Transformation::setProjection(
    bool ortho, float l, float r, float b, float t, float n, float f)
{
    ortho_ = ortho;
    p_l_ = l;
    p_r_ = r;
    p_b_ = b;
    p_t_ = t;
    p_n_ = n;
    p_f_ = f;
    proj_ = ortho_
            ? glm::ortho(l, r, b, t, n, f)
            : glm::frustum(l, r, b, t, n, f);
}

} // ns
} // ns