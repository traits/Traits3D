#pragma once

#include "traits3d/glbase/transformation.h"

Traits3D::GL::Transformation::Transformation()
{
  // dummy
}

void Traits3D::GL::Transformation::set(glm::mat4 const& proj, glm::mat4 const& mv
  , bool ortho, float l, float r, float b, float t, float n, float f)
{
  proj_ = proj;
  mv_ = mv;

  ortho_ = ortho;
  p_l_ = l;
  p_r_ = r;
  p_b_ = b;
  p_t_ = t;
  p_n_ = n;
  p_f_ = f;
}

