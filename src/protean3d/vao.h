#pragma once

#include <vector>
#include "glhelper.h"
#include "types.h"
#include "ibo.h"

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

      bool appendIBO(size_t xsize, size_t ysize, GLenum primitive_type);
            size_t iboCount() const { return ibos_.size(); }
      bool drawIBO(size_t idx, GLenum draw_type);

    private:
      GLuint id_ = 0;

      std::vector<IBO> ibos_;

      void unbind();
    };

    // implementation
  } // ns
} // ns