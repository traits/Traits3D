#pragma once

#if defined PROTEAN3D_GL_IS_OPENGL
  #include <glloadgen/GL_3_3/gl_core_3_3.h>
#elif defined PROTEAN3D_GL_IS_OPENGL_ES
  #include <GLES3/gl3.h> 
#else
  #include <glloadgen/GL_3_3/gl_core_3_3.h>
#endif

#include "glm/glm.hpp"