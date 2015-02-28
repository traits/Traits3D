#pragma once

//
// Create DLL if EXAMPLE_DLL is defined (Windows only)
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

  #if defined(EXAMPLE_NODLL)
    #undef EXAMPLE_MAKEDLL
    #undef EXAMPLE_DLL
    #undef EXAMPLE_TEMPLATEDLL
  #endif

  #ifdef EXAMPLE_DLL
    #if defined(EXAMPLE_MAKEDLL)     /* create a DLL */
      #undef EXAMPLE_DLL
      #define EXAMPLE_EXPORT  __declspec(dllexport)
      #define EXAMPLE_TEMPLATEDLL
    #endif
  #endif

  #if defined(EXAMPLE_DLL)     /* use a DLL */
    #define EXAMPLE_EXPORT  __declspec(dllimport)
    #define EXAMPLE_TEMPLATEDLL
  #endif

#else // ! Windows
  #undef EXAMPLE_MAKEDLL       /* ignore these for other platforms */
  #undef EXAMPLE_DLL
  #undef EXAMPLE_TEMPLATEDLL
#endif

#ifndef EXAMPLE_EXPORT
  #define EXAMPLE_EXPORT
#endif


