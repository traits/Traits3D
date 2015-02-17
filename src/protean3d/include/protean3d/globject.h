#pragma once

#include "protean3d/glbase/shader.h"
#include "protean3d/glbase/vao.h"
#include "protean3d/glbase/vbo.h"
#include "protean3d/glbase/ibo.h"

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
