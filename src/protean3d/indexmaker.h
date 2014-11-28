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

    enum class RestartType
    {
      DegeneratedElements,
      PrimitiveRestart
    };

    bool create(std::vector<GLuint>& result, RestartType& restart_type, GLuint xsize, GLuint ysize, GLenum drawType);

  private:
    bool createLineStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize);
    bool createTriangleStrips(std::vector<GLuint>& result, GLuint xsize, GLuint ysize);
  };

}
}