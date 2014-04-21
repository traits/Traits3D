#pragma once

//#ifdef __cplusplus
//extern "C" {
//#endif 

#if defined PROTEAN3D_GL_IS_OPENGL
  #if PROTEAN3D_GL_VERSION_MAJOR >= 4
    #include <glloadgen/GL_4_2/gl_core_4_2.h>
  #else
    #include <glloadgen/GL_3_3/gl_core_3_3.h>
  #endif
#elif defined PROTEAN3D_GL_IS_OPENGL_ES
  // ES header here
#else
  #include <glloadgen/GL_3_3/gl_core_3_3.h>
#endif

//#ifdef __cplusplus
//}
//#endif 