#pragma once

#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/matrix_inverse.hpp>
#include "traits3d/glbase/transformation.h"

Traits3D::GL::Transformation::Transformation()
{
  // dummy
}

/**
 \param mv The model-view matrix to set
 \param n  The normal transformation matrix to set (mat3(mv)^-1^T)
 */
void Traits3D::GL::Transformation::setModelView(glm::mat4 const& mv, glm::mat3 const& n, glm::mat4 const& t)
{
  mv_ = mv;
  normal_mat_ = n;
  light_mat_ = t;
}

void Traits3D::GL::Transformation::setProjection(glm::mat4 const& proj)
{
  proj_ = proj;
}

void Traits3D::GL::Transformation::setProjection(
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

