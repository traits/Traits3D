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
    class PROTEAN3D_EXPORT IBO
    {
    public:
      IBO();
      virtual ~IBO() = default;
      GLuint id() const { return id_; } //!< IBO index
      size_t size() const { return size_; } //! buffer size in sizeof(GLuint)

      bool bindData(std::vector<GLuint> const &data, GLenum drawtype);

    private:
      GLuint id_;
      size_t size_; //buffer size
    };
  } // ns
} // ns