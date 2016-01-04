#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/matrix_inverse.hpp>
#include "glb/transformation.h"

namespace glb
{

Transformation::Transformation()
{
    ortho_ = true;
    p_l_ = 0.0f;
    p_r_ = 0.0f;
    p_b_ = 0.0f;
    p_t_ = 0.0f;
    p_n_ = 0.0f;
    p_f_ = 0.0f;
}

/**
\param mv The model-view matrix to set
*/
void Transformation::setModelView(glm::vec3 const &translation, glm::mat4 const &rotation, glm::vec3 const &scale)
{
    translation_ = translation;
    rotation_ = rotation;
    scale_ = scale;
    glm::mat4 mscale = glm::scale(glm::mat4(1.0f), scale_);
    glm::mat4 mtranslate = glm::translate(glm::mat4(1.0f), translation_);
    mv_ = mtranslate * rotation_ * mscale;
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
