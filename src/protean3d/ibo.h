#pragma once

#include <vector>
#include "glhelper.h"
#include "types.h"

namespace Protean3D
{
  //! Projects GL namespace
  namespace GL
  {
    //! Index Buffer Objects
    class IBO
    {
    public:
      IBO();
      virtual ~IBO() = default;
      GLuint id() const { return id_; } //!< IBO index
      size_t size() const { return size_; } //! buffer size in sizeof(GLuint)
      
      bool create(size_t xsize, size_t ysize, GLenum primitive_type);
      bool bindData(GLenum drawtype);

    private:
      GLuint id_;
      size_t size_; //buffer size
      std::vector<GLuint> indexes_;
    };
  } // ns
} // ns