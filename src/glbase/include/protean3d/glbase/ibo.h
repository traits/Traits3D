#pragma once

#include <vector>
#include "protean3d/glbase/glhelper.h"
#include "protean3d/glbase/indexmaker.h"

namespace Protean3D
{
  //! Projects GL namespace
  namespace GL
  {
    class VAO;

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
      IndexMaker indexmaker_;
      GLenum primitive_type_ = GL_TRIANGLE_STRIP;
      VAO* vao_;

      bool bindData(GLenum draw_type);
    };
  } // ns
} // ns