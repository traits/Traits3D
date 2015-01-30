#pragma once

#include <vector>
#include "protean3d/glbase/glhelper.h"

namespace Protean3D
{
  //! Projects GL namespace
  namespace GL
  {
    //! Unifies buffer handling the VAO way
    class VAO
    {
    public:
      VAO();
      virtual ~VAO();
      void bind();

    private:
      GLuint id_ = 0;

      void unbind();
    };

    // implementation
  } // ns
} // ns