#pragma once

#include "shader.h"
#include "vao.h"

namespace Protean3D
{
  namespace GL
  {
    class Object
    {
    public:
      Object();
      virtual ~Object() = default;
      virtual void draw() = 0;
      void setProjectionMatrix(glm::mat4 const& mat);
      void setModelViewMatrix(glm::mat4 const& mat);

    protected:
      //std::vector<GL::Shader> shader_p;
      GL::VAO vao_p;
      glm::mat4 projection_matrix_p;
      glm::mat4 modelview_matrix_p;
    };
  } // ns
} // ns
