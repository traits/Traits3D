#pragma once

#include "glm/glm.hpp"

namespace Traits3D
{
  //! Projects GL namespace
  namespace GL
  {
    //! Index Buffer Objects
    class Transformation
    {
    public:
      Transformation();
      ~Transformation() = default;

      glm::mat4 const& mv() const { return mv_; }
      glm::mat4 const& proj() const { return proj_; }
      void setModelView(glm::mat4 const& mv);
      void setProjection(bool ortho, float l, float r, float b, float t, float n, float f);

      float proj_l() const { return p_l_; }
      float proj_r() const { return p_r_; }
      float proj_b() const { return p_b_; }
      float proj_t() const { return p_t_; }
      float proj_n() const { return p_n_; }
      float proj_f() const { return p_f_; }

    private:
      glm::mat4 mv_;      
      glm::mat4 proj_;

      bool ortho_ = true;
      float p_l_ = 0.0f;
      float p_r_ = 0.0f;
      float p_b_ = 0.0f;
      float p_t_ = 0.0f;
      float p_n_ = 0.0f;
      float p_f_ = 0.0f;
    };
  } // ns
} // ns