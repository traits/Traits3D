#pragma once

#include <vector>
#include "glhelper.h"
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

      void bind() { glBindVertexArray(idx_); }
      void unbind() { glBindVertexArray(0); }

      //! Returns index of new element or std::numeric_limits<size_t>::max() in case of errors
      template<typename PRIMITIVE>
      size_t appendVBO(std::vector<PRIMITIVE> const& data, VBO::PrimitiveLayout const& descr, GLuint program, const char* attr_name, GLenum draw_type = GL_STATIC_DRAW);

      //! Returns index of new element or std::numeric_limits<size_t>::max() in case of errors
      size_t appendIBO(std::vector<GLuint> const& data, GLenum draw_type = GL_STATIC_DRAW);

      template<typename PRIMITIVE>
      bool updateVBO(size_t idx, std::vector<PRIMITIVE> const& data);

      size_t vboCount() const { return vbos_.size(); }
      size_t iboCount() const { return ibos_.size(); }

    private:
      GLuint idx_;

      std::vector<VBO> vbos_;
      std::vector<IBO> ibos_;
    };

    // implementation

    template<typename PRIMITIVE>
    size_t Protean3D::GL::VAO::appendVBO(std::vector<PRIMITIVE> const& data, VBO::PrimitiveLayout const& descr
      ,GLuint program, const char* attr_name, GLenum draw_type /*= GL_STATIC_DRAW*/)
    {
      //static_assert(std::is_same<PRIMITIVE, GLfloat>::value, "Incorrect buffer type!");
      VBO buffer;
      if (buffer.create(descr, program, attr_name, draw_type ))
      {
        if (!data.empty() && !buffer.update(data))
          return std::numeric_limits<size_t>::max();

        vbos_.push_back(buffer);
        return vbos_.size()-1;
      }
      return std::numeric_limits<size_t>::max();
    }

    template<typename PRIMITIVE>
    bool Protean3D::GL::VAO::updateVBO(size_t idx, std::vector<PRIMITIVE> const& data)
    {
      if (idx >= vboCount())
        return false;

      return vbos_[idx].update(data);
    }

  } // ns
} // ns