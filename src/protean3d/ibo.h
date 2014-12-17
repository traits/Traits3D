#pragma once

#include <vector>
#include "glhelper.h"
#include "types.h"
#include "vao.h"
#include "indexmaker.h"

namespace Protean3D
{
  //! Projects GL namespace
  namespace GL
  {
    //! Index Buffer Objects
    class IBO
    {
    public:
      explicit IBO(VAO* vao);
      virtual ~IBO() = default;
      //GLuint id() const { return id_; } //!< IBO index
      //size_t size() const { return size_; } //! buffer size in sizeof(GLuint)
      //GLenum primitiveType() const { return primitive_type_; } //! GL_TRIANGLE_STRIP etc.
      
      bool create(size_t xsize, size_t ysize, GLenum primitive_type);
      bool draw(GLenum draw_type);

    private:
      GLuint id_ = 0;
      size_t size_ = 0; //buffer size
      std::vector<GLuint> indexes_;
      IndexMaker indexmaker_;
      GLenum primitive_type_ = GL_TRIANGLE_STRIP;
      IndexMaker::RestartType restart_type_ = IndexMaker::RestartType::DegeneratedElements;
      VAO* vao_;

      bool bindData(GLenum draw_type);
    };
  } // ns
} // ns