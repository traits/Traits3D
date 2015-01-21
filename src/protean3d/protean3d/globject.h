#pragma once

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ibo.h"

namespace Protean3D
{
  namespace GL
  {
    class Object
    {
    public:
      Object();
      virtual ~Object() = default;
      virtual void draw(glm::mat4 const& proj_matrix, glm::mat4 const& mv_matrix) = 0;

    protected:
      GL::VAO vao_p;
    };
  } // ns
} // ns
