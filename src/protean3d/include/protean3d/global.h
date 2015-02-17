#pragma once

#define PROTEAN3D_MAJOR_VERSION 0
#define PROTEAN3D_MINOR_VERSION 3
#define PROTEAN3D_PATCH_VERSION 0

//
// Create DLL if PROTEAN3D_DLL is defined (Windows only)
//

#if defined(_WIN32) || defined(_WIN64)
  #if defined(_MSC_VER) /* MSVC Compiler */
    #pragma warning(disable: 4251) // dll interface required for stl templates
    //pragma warning(disable: 4244) // 'conversion' conversion from 'type1' to 'type2', possible loss of data
    #pragma warning(disable: 4786) // truncating debug info after 255 characters
    #pragma warning(disable: 4660) // template-class specialization 'identifier' is already instantiated
    #if (_MSC_VER >= 1400) /* VS8 - not sure about VC7 */
      #pragma warning(disable: 4996) /* MS security enhancements */
    #endif
  #endif

  #if defined(PROTEAN3D_NODLL)
    #undef PROTEAN3D_MAKEDLL
    #undef PROTEAN3D_DLL
    #undef PROTEAN3D_TEMPLATEDLL
  #endif

  #ifdef PROTEAN3D_DLL
    #if defined(PROTEAN3D_MAKEDLL)     /* create a DLL */
      #undef PROTEAN3D_DLL
      #define PROTEAN3D_EXPORT  __declspec(dllexport)
      #define PROTEAN3D_TEMPLATEDLL
    #endif
  #endif

  #if defined(PROTEAN3D_DLL)     /* use a DLL */
    #define PROTEAN3D_EXPORT  __declspec(dllimport)
    #define PROTEAN3D_TEMPLATEDLL
  #endif

#else // ! Windows
  #undef PROTEAN3D_MAKEDLL       /* ignore these for other platforms */
  #undef PROTEAN3D_DLL
  #undef PROTEAN3D_TEMPLATEDLL
#endif

#ifndef PROTEAN3D_EXPORT
  #define PROTEAN3D_EXPORT
#endif


