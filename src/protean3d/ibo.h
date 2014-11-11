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
      IBO() : id_(0), draw_type_(GL_STATIC_DRAW), size_(0) {}
      virtual ~IBO() = default;
      GLuint id() const { return id_; } //!< IBO index
      //size_t size() const { return size_; } //! buffer size in sizeof(GLuint)

      bool create(std::vector<GLuint> const& data, GLenum drawtype = GL_STATIC_DRAW);
      
    private:
      GLuint id_;
      GLenum draw_type_;
      size_t size_; //buffer size
    };
  } // ns
} // ns