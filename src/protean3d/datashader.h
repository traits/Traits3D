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
      std::vector<VAO> vaos;
      std::vector<Shader> shaders;

    private:
    };
  } // ns
} // ns



