#pragma once

#include <vector>
#include "glhelper.h"

namespace Protean3D
{
namespace GL
{
    
  class IndexMaker
  {
  public:
    IndexMaker();

    enum class Flag
    {
      Normal,
      PrimitiveRestart
    };

    bool create(std::vector<GLuint>& result, GLuint xsize, GLuint ysize, GLenum drawType);
    Flag flag() const { return flag_; }

  private:
    bool createLineStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize);
    bool createTriangleStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize);
    Flag flag_;
  };

}
}