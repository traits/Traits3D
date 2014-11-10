#pragma once

#include <vector>
#include "glhelper.h"
#include "types.h"

namespace Protean3D
{
  //! Projects GL namespace
  namespace GL
  {
    //! Vertex Buffer Objects
    class PROTEAN3D_EXPORT VBO
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

      VBO() : id_(0), draw_type_(GL_STATIC_DRAW), bsize_(0) {}
      virtual ~VBO() = default;
      GLuint id() const { return id_; } //!< VBO index

      bool create(PrimitiveLayout const& descr, GLenum drawtype = GL_STATIC_DRAW);

      template <typename PRIMITIVE>
      bool update(std::vector<PRIMITIVE> const& data, GLuint program, const char* attr_name);

      
    private:
      GLuint id_;
      GLenum draw_type_;
      PrimitiveLayout description_;
      size_t bsize_; //buffer size in byte
    };

    template <typename PRIMITIVE>
    bool Protean3D::GL::VBO::update(std::vector<PRIMITIVE> const& data, GLuint program, const char* attr_name)
    {
      glBindBuffer(GL_ARRAY_BUFFER, id_);

      size_t bsize = sizeof(PRIMITIVE) * data.size();

      if (!bsize_ || bsize_ != bsize)
        glBufferData(GL_ARRAY_BUFFER, bsize, bsize ? &data[0] : nullptr, draw_type_);
      else
        glBufferSubData(GL_ARRAY_BUFFER, 0, bsize, bsize ? &data[0] : nullptr);

      bsize_ = bsize;

      GLenum err = glGetError();
      switch (err)
      {
      case GL_INVALID_ENUM:
      case GL_INVALID_OPERATION:
      case GL_OUT_OF_MEMORY:
        return false;
      default:
        break;
      }

      GLuint attrloc;
      attrloc = glGetAttribLocation(program, attr_name);
      glVertexAttribPointer(attrloc, description_.components, description_.type, GL_FALSE, description_.stride, description_.offset);
      glEnableVertexAttribArray(attrloc);

      return true;
    }
  } // ns
} // ns