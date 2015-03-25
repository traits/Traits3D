#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "traits3d/glbase/transformation.h"

Traits3D::GL::Transformation::Transformation()
{
  // dummy
}

void Traits3D::GL::Transformation::setModelView(glm::mat4 const& mv)
{
  mv_ = mv;
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
