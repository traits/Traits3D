#pragma once

#include <vector>
#include "traits3d/glbase/glhelper.h"

namespace Traits3D
{
namespace GL
{
    
  class IndexMaker
  {
  public:
    IndexMaker();

    enum class RestartType
    {
      None,
      PrimitiveRestart
    };

    using IndexType = GLuint;
    using Container = std::vector < std::vector<IndexType> >;
    void setRestartBehavior(RestartType rtype, IndexType placeholder = 0);  
    RestartType restartType() const { return restart_type_; }
    IndexType restartPLaceholder() const { return restart_placeholder_; }

    bool create(GLuint xsize, GLuint ysize, GLenum primitive_type);
    const Container& container() const { return container_; }
    size_t linearSize() const
    {
      size_t ret = 0;
      for (auto const& a : container_)
        ret += a.size();
      
      return ret;
    }

  private:
    Container container_;

    IndexType restart_placeholder_;
    RestartType restart_type_ = RestartType::None;

    bool createLineStrips(Container& result, GLuint xsize, GLuint ysize);
    bool createRestartLineStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize);
    bool createTriangleStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize);
    bool createRestartTriangleStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize);
  };

}
}