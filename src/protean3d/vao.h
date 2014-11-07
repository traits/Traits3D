#pragma once

#include <vector>
#include "gl_layer.h"
#include "types.h"
#include "vbo.h"
#include "ibo.h"

namespace Protean3D
{
  //! Projects GL namespace
  namespace GL
  {
    //! Unifies buffer handling the VAO way
    class PROTEAN3D_EXPORT VAO
    {
    public:
      VAO();
      virtual ~VAO();

      template<typename PRIMITIVE>
      inline bool appendVBO(std::vector<PRIMITIVE> const& data, VBO::PrimitiveLayout const& descr, bool dynamic = false);

    private:
      GLuint vao_;

      std::vector<VBO> vbos_;
      IBO ibo_;
    };

    // implementation

    template<typename PRIMITIVE>
    bool Protean3D::GL::VAO::appendVBO(std::vector<PRIMITIVE> const& data, VBO::PrimitiveLayout const& descr, bool dynamic /*= false*/)
    {
      //static_assert(std::is_same<PRIMITIVE, GLfloat>::value, "Incorrect buffer type!");
      VBO vbo;
      if (vbo.create(data, descr, dynamic))
      {
        vbos_.push_back(vbo);
        return true;
      }
      return false;
    }


  } // ns
} // ns