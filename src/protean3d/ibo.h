#pragma once

#include <vector>
#include "gl_layer.h"
#include "types.h"

namespace Protean3D
{
  //! Projects GL namespace
  namespace GL
  {
    //! Index Buffer Objects
    class /*PROTEAN3D_EXPORT*/ IBO
    {
    public:
      IBO() : id_(0){}
      virtual ~IBO() = default;
      GLuint id() const { return id_; } //!< IBO index

      bool create(std::vector<GLuint> const& data, bool dynamic = false);
      
    private:
      GLuint id_;
      bool create_(GLuint const* data, size_t dsize, bool dynamic = false);
    };
  } // ns
} // ns