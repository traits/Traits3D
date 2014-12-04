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
    class VBO
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
        size_t offset; // offset in byte 
      };

      explicit VBO(PrimitiveLayout const& descr);
      virtual ~VBO() = default;
      GLuint id() const { return id_; } //!< VBO index

      template <typename PRIMITIVE>
      bool bindData(std::vector<PRIMITIVE> const& data, GLenum drawtype);

      bool bindShader(GLuint program_id, std::string attr_name);

    private:
      GLuint id_;
      PrimitiveLayout description_;
      size_t bsize_; //buffer size in byte
      GLuint program_;
      std::string attr_name_;
    
      bool bindAttribute(GLuint attr_location);
    };

    template <typename PRIMITIVE>
    bool Protean3D::GL::VBO::bindData(std::vector<PRIMITIVE> const& data, GLenum drawtype)
    {
      glBindBuffer(GL_ARRAY_BUFFER, id_);

      GLint oldtype;
      glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &oldtype);
      if (GL_NO_ERROR != glGetError())
        return false;

      size_t bsize = sizeof(PRIMITIVE) * data.size();
      if (!bsize_ || bsize_ != bsize || static_cast<GLenum>(oldtype) != drawtype)
        glBufferData(GL_ARRAY_BUFFER, bsize, bsize ? &data[0] : nullptr, drawtype);
      else
        glBufferSubData(GL_ARRAY_BUFFER, 0, bsize, bsize ? &data[0] : nullptr);

      if (GL_NO_ERROR != glGetError())
        return false;

      bsize_ = bsize;
      return true;
    }
  } // ns
} // ns

