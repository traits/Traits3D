#pragma once

#include "glm/glm.hpp"

namespace Traits3D
{
  //! Projects GL namespace
  namespace GL
  {
    //! Index Buffer Objects
    class MatrixStack
    {
    public:
      MatrixStack();
      ~MatrixStack() = default;

      glm::mat4 const& mv() const { return mv_; };
      glm::mat4 const& proj() const { return proj_; };
      void set(glm::mat4 const& proj, glm::mat4 const& mv)
      {
        proj_ = proj;
        mv_ = mv;
      }


    private:
      glm::mat4 mv_;
      glm::mat4 rotate_;
      glm::mat4 translate_;
      glm::mat4 scale_;
      
      glm::mat4 proj_;
    };
  } // ns
} // ns