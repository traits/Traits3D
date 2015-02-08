#pragma once

#include <vector>
#include "protean3d/glbase/glhelper.h"

namespace Protean3D
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
      DegeneratedElements,
      PrimitiveRestart
    };

    using IndexType = GLuint;
    using Container = std::vector < std::vector<IndexType> >;
    bool create(RestartType& restart_type, GLuint xsize, GLuint ysize, GLenum primitive_type);
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

    static const IndexType restart_place_holder_;

    bool createLineStrips(Container& result, GLuint xsize, GLuint ysize);
    bool createRestartLineStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize);
    bool createTriangleStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize);
    bool createRestartTriangleStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize);
  };

}
}