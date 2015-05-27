#pragma once

#include "traits3d/glbase/shader.h"
#include "traits3d/glbase/vao.h"
#include "traits3d/glbase/vbo.h"
#include "traits3d/glbase/ibo.h"

namespace Traits3D
{
  namespace GL
  {
    class Transformation;

    class Object
    {
      public:
        Object() = default;
        virtual ~Object() = default;
        virtual void draw(Transformation const& matrices) = 0;

      protected:
        GL::VAO vao_p;
    };
  } // ns
} // ns
