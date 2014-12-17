#pragma once

#include <vector>
#include "glhelper.h"
#include "types.h"

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