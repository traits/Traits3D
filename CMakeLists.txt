CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

# remove configurations RelWithDebInfo etc. 
# http://www.cmake.org/Wiki/CMake_FAQ
if(CMAKE_CONFIGURATION_TYPES)
   set(CMAKE_CONFIGURATION_TYPES Debug Release)
   set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
     "Reset the configurations to what we need"
     FORCE)
 endif()

# http://www.volumesoffun.com/tag/cmake/
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

PROJECT("Traits3D")
set(CMAKE_DEBUG_POSTFIX "D")

include("CMakeDependentOption")
include("cmake/macros.cmake")
include("cmake/functions.cmake")

# search local cmake stuff
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Build & Install directories
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/../install CACHE PATH "Install directory" FORCE)

# Set dedicated output directory, so we have all the libs/dll's and executables gathered at one place for debugging
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# initialize with true
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Target OS
set(TRAITS3D_OS "Windows" CACHE STRING "Target OS")
set_property(CACHE TRAITS3D_OS PROPERTY STRINGS "Windows")
#MB todo set_property(CACHE TRAITS3D_OS PROPERTY STRINGS "Windows" "Linux" "Android" "iOS" "emscripten")

# OpenGL Context Provider
option(TRAITS3D_EXAMPLES_GLFW "GLFW" ON)
option(TRAITS3D_EXAMPLES_QT "Qt" ON)

# OpenGL Version Provider
set(TRAITS3D_GL_VARIANT "OPENGL" CACHE STRING "OpenGL Variant (OpenGL, OpenGL ES, WebGL)")
set_property(CACHE TRAITS3D_GL_VARIANT PROPERTY STRINGS "OPENGL" "OPENGL_ES" "WEBGL")

if ("${TRAITS3D_GL_VARIANT}"  STREQUAL "OPENGL")
  set(TRAITS3D_GL_MAJOR "3" CACHE STRING "OpenGL major number")
  set_property(CACHE TRAITS3D_GL_MAJOR PROPERTY STRINGS "2" "3" "4")
  set(TRAITS3D_GL_MINOR "3" CACHE STRING "OpenGL minor number")
  set_property(CACHE TRAITS3D_GL_MINOR PROPERTY STRINGS "0" "1" "2" "3" "3" "5")
elseif ("${TRAITS3D_GL_VARIANT}"  STREQUAL "OPENGL_ES")
  set(TRAITS3D_GL_MAJOR "2" CACHE STRING "OpenGL ES major number")
  set_property(CACHE TRAITS3D_GL_MAJOR PROPERTY STRINGS "2" "3")
  set(TRAITS3D_GL_MINOR "0" CACHE STRING "OpenGL ES minor number")
  set_property(CACHE TRAITS3D_GL_MINOR PROPERTY STRINGS "0" "1")
endif()
add_definitions(-DTRAITS3D_GL_IS_${TRAITS3D_GL_VARIANT})
add_definitions(-DTRAITS3D_GL_MAJOR=${TRAITS3D_GL_MAJOR})
add_definitions(-DTRAITS3D_GL_MINOR=${TRAITS3D_GL_MINOR})

# Text Engine
set(TRAITS3D_TEXT "stb" CACHE STRING "Text Engine")
set_property(CACHE TRAITS3D_TEXT PROPERTY STRINGS "stb" "freetype" "Qt")
if ("${TRAITS3D_TEXT}"  STREQUAL "stb")
  add_definitions(-DTEXTENGINE_STB)
elseif ("${TRAITS3D_TEXT}"  STREQUAL "freetype")
  add_definitions(-DTEXTENGINE_FREETYPE)
endif()

add_subdirectory(src)

option(TARGET_GLES "Build for OpenGL ES instead of desktop OpenGL" OFF)
CMAKE_DEPENDENT_OPTION(TARGET_GLES2 "Build for OpenGL ES 2" ON "TARGET_GLES" OFF)
CMAKE_DEPENDENT_OPTION(TARGET_DESKTOP_GLES "Build for OpenGL ES on desktop" OFF "TARGET_GLES" OFF)

option(TRAITS3D_EXAMPLES "Build examples" ON)
# CMAKE_DEPENDENT_OPTION(TRAITS3D_EXAMPLES "Build examples" ON "\"\${TRAITS3D_EXAMPLES_GL_CONTEXT}\"  STREQUAL \"Qt\"" OFF)

#MB todo
# set(TRAITS3D_GL_HEADER_PATH "" CACHE PATH "OpenGL header root")
# set(TRAITS3D_GL_HEADERS "EGL/h0.h" "h1.h" CACHE STRING "OpenGL headers")
# set(TRAITS3D_GL_SOURCES "" CACHE FILEPATH "OpenGL sources")
# set(TRAITS3D_GL_LIBRARIES "h0.lib" "h1.lib" CACHE STRING "OpenGL libraries")
# set(TRAITS3D_GL_LIBRARY_PATH "" CACHE PATH "OpenGL library root")
# TRAITS3D_WRITE_GL_CONFIGURATION("${TRAITS3D_GL_HEADERS}")

if (TRAITS3D_EXAMPLES)
  add_subdirectory(examples)
endif()


