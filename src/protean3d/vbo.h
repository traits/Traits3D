#pragma once

#include <vector>
#include "gl_layer.h"
#include "types.h"

namespace Protean3D
{
  //! Projects GL namespace
  namespace GL
  {
    //! Vertex Buffer Objects
    class /*PROTEAN3D_EXPORT*/ VBO
    {
    public:
      class PrimitiveLayout
      {
      public:
        explicit PrimitiveLayout(char c = 0, GLenum t = GL_FLOAT, GLsizei s = 0, unsigned o = 0) 
          : components(c), type(t), stride(s), offset(o)
        {}
        char components; // 1..4
        GLenum type; // GL_BYTE, GL_UNSIGNED_BYTE, GL_FLOAT //TODO GL_HALF_FLOAT 
        GLsizei stride;
        unsigned offset; // offset in byte 
      };

      VBO() : id_(0){}
      virtual ~VBO() = default;
      GLuint id() const { return id_; } //!< VBO index

      template <typename PRIMITIVE>
      bool create(std::vector<PRIMITIVE> const& data, PrimitiveLayout const& descr, bool dynamic = false);
      
    private:
      GLuint id_;
      PrimitiveLayout description_;

      template <typename PRIMITIVE>
      bool create_(PRIMITIVE const* data, size_t dsize, PrimitiveLayout const& descr, bool dynamic = false);
    };

    // implementation

    template <typename PRIMITIVE>
    bool Protean3D::GL::VBO::create_(PRIMITIVE const* data, size_t dsize, PrimitiveLayout const& descr, bool dynamic /*= false*/)
    {
      glGenBuffers(1, &id_);
      if (GL_INVALID_VALUE == glGetError())
        return false;

      glBindBuffer(GL_ARRAY_BUFFER, id_);
      glBufferData(GL_ARRAY_BUFFER, sizeof(PRIMITIVE) * dsize, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
      GLenum err = glGetError();

      switch (err)
      {
      case GL_INVALID_OPERATION :
      case GL_OUT_OF_MEMORY :
        return false;
      default:
        return true;
      }
    }

    template <typename PRIMITIVE>
    bool Protean3D::GL::VBO::create(std::vector<PRIMITIVE> const& data, PrimitiveLayout const& descr, bool dynamic /*= false*/)
    {
       return create_(&data[0], data.size(), descr, dynamic);
    }


  } // ns
} // ns