#pragma once

#include <vector>
#include "protean3d/glbase/glhelper.h"

namespace Protean3D
{
  //! Projects GL namespace
  namespace GL
  {
    class VAO;
    //! Vertex Buffer Objects
    class VBO
    {
    public:
      explicit VBO(VAO* vao);
      virtual ~VBO() = default;
      GLuint id() const { return id_; } //!< VBO index
      
      bool setData(std::vector<glm::vec3> const& data, bool setdrawtype = false, GLenum drawtype = GL_STATIC_DRAW);
      bool setData(std::vector<glm::vec4> const& data, bool setdrawtype = false, GLenum drawtype = GL_STATIC_DRAW);

      bool bindAttribute(GLuint attr_location);
      //! Draw complete buffer as GL_TRIANGLE_STRIP etc.
      bool draw(GLenum primitive_type);
      //! Draw partial buffer
      bool draw(GLenum primitive_type, size_t first, size_t count);

    private:
      class Layout
      {
      public:
        explicit Layout(char c = 0, GLenum t = GL_FLOAT, GLsizei s = 0, unsigned o = 0)
          : components(c), type(t), stride(s), offset(o)
        {}
        char components; // 1..4
        GLenum type; // GL_BYTE, GL_UNSIGNED_BYTE, GL_FLOAT //TODO GL_HALF_FLOAT 
        GLsizei stride;
        size_t offset; // offset in byte 

        bool match(const Layout& layout)
        {
          if (initialized() && layout != *this)
            return false;

          *this = layout;
          return true;
        }

      private: 
        bool operator!=(const Layout& r) const
        {
          return components != r.components
            || type != r.type
            || stride != r.stride  //todo
            || offset != r.offset; //todo
        }

        bool initialized() const { return 0 < components; }
      };

      GLuint id_;
      Layout layout_;
      size_t bsize_ = 0; //buffer size in byte
      size_t primitive_size_ = 1;
      GLuint program_;
      std::string attr_name_;
      VAO* vao_; // non-owning pointer

      template <typename PRIMITIVE>
      bool setData(std::vector<PRIMITIVE> const& data, bool setdrawtype = false, GLenum drawtype = GL_STATIC_DRAW);
    };


    /**
     Bind data.
    
     \param data        The data.
     \param setdrawtype if true, consider the following argument
     \param drawtype    GL_STATIC_DRAW etc.

     \return true if it succeeds, false if it fails.
     */
    template <typename PRIMITIVE>
    bool Protean3D::GL::VBO::setData(std::vector<PRIMITIVE> const& data, bool setdrawtype/* = false*/, GLenum drawtype /*= GL_STATIC_DRAW*/)
    {
      if (data.empty())
        return false;

      vao_->bind();

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
      primitive_size_ = sizeof(PRIMITIVE);
      return true;
    }

  } // ns
} // ns
