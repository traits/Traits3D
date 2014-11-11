#pragma once

#include "vao.h"
#include "shader.h"

namespace Protean3D
{
  namespace GL
  {
    //! Pairs data and shader, working on these data 
    class PROTEAN3D_EXPORT DataShader
    {
    public:
      VAO vao;
      Shader shader;

    private:
    };
  } // ns
} // ns



