CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT("Protean3D")
set(CMAKE_DEBUG_POSTFIX "D")

# include("CMakeDependentOption")
include("cmake/macros.cmake")

# search local cmake stuff
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Build & Install directories
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../protean3d_install CACHE PATH "Install directory" FORCE)
set(dir ${CMAKE_CURRENT_SOURCE_DIR}/../protean3d_build)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)

# Target OS
set(PROTEAN3D_OS "Windows" CACHE STRING "Target OS")
set_property(CACHE PROTEAN3D_OS PROPERTY STRINGS "Windows" "Linux" "Android" "iOS" "emscripten")

# OpenGL Context Provider
set(PROTEAN3D_GL_CONTEXT "GLFW" CACHE STRING "OpenGL Context Provider")
set_property(CACHE PROTEAN3D_GL_CONTEXT PROPERTY STRINGS "Qt" "GLFW")

# OpenGL Variant Provider
set(PROTEAN3D_GL_VERSION "GL3" CACHE STRING "OpenGL (ES) Version")
set_property(CACHE PROTEAN3D_GL_VERSION PROPERTY STRINGS "GL3" "GL4" "ES2" "ES3")

# Font Provider
set(PROTEAN3D_TEXT "Core" CACHE STRING "Font/String Provider")
set_property(CACHE PROTEAN3D_TEXT PROPERTY STRINGS "Core" "freetype" "Qt")

add_subdirectory(src)

option(PROTEAN3D_EXAMPLES "Build examples" ON)
# CMAKE_DEPENDENT_OPTION(PROTEAN3D_EXAMPLES "Build examples" ON "\"\${PROTEAN3D_GL_CONTEXT}\"  STREQUAL \"Qt\"" OFF)

if (PROTEAN3D_EXAMPLES)
  add_subdirectory(examples)
endif()


