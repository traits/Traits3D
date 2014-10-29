#pragma once

#include <vector>
#include "gl_layer.h"
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

      template<typename PRIMITIVE>
      inline bool appendVBO(std::vector<PRIMITIVE> const& data, bool dynamic = false);
      bool appendIndexVBO(std::vector<GLuint> const& data, bool dynamic = false);

    private:
      GLuint vao_;

      typedef std::pair<GLenum, GLuint> VBOinfo;
      std::vector<VBOinfo> vbos_;

      template<typename PRIMITIVE>
      bool appendVBO_(GLenum type, PRIMITIVE const* data, size_t dsize, bool dynamic = false);

    };

    // implementation

    template<typename PRIMITIVE>
    bool Protean3D::GL::VAO::appendVBO_(GLenum type, PRIMITIVE const* data, size_t dsize, bool dynamic /*= false*/)
    {
      if (!vao_)
        return false;

      GLuint vbo;
      glGenBuffers(1, &vbo);
      if (GL_INVALID_VALUE == glGetError())
        return false;

      glBindVertexArray(vao_);
      if (GL_INVALID_VALUE == glGetError())
        return false;

      glBindBuffer(type, vbo);
      glBufferData(type, sizeof(PRIMITIVE) * dsize, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
      GLenum err = glGetError();

      if (GL_INVALID_OPERATION == err || GL_OUT_OF_MEMORY == err)
      {
        glBindVertexArray(0);
        return false;
      }
      glBindVertexArray(0);
      vbos_.push_back(VBOinfo(type,vbo));
      return true;
    }

    template<typename PRIMITIVE>
    bool Protean3D::GL::VAO::appendVBO(std::vector<PRIMITIVE> const& data, bool dynamic /*= false*/)
    {
      return appendVBO_(GL_ARRAY_BUFFER, &data[0], data.size(), dynamic);
    }


  } // ns
} // ns