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

# OpenGL Version Provider
set(PROTEAN3D_GL_VARIANT "GL" CACHE STRING "OpenGL (ES) Variant")
set_property(CACHE PROTEAN3D_GL_VARIANT PROPERTY STRINGS "GL" "ES" "WEBGL")

set(PROTEAN3D_GL_VERSION_MAJOR "3" CACHE STRING "OpenGL Major Version")
set_property(CACHE PROTEAN3D_GL_VERSION_MAJOR PROPERTY STRINGS "3" "4")

set(PROTEAN3D_GL_VERSION_MINOR "3" CACHE STRING "OpenGL Minor Version")
set_property(CACHE PROTEAN3D_GL_VERSION_MINOR PROPERTY STRINGS "0" "1" "2" "3" "4")

# Font Provider
set(PROTEAN3D_TEXT "Core" CACHE STRING "Font/String Provider")
set_property(CACHE PROTEAN3D_TEXT PROPERTY STRINGS "Core" "freetype" "Qt")

add_subdirectory(src)

option(PROTEAN3D_EXAMPLES "Build examples" ON)
# CMAKE_DEPENDENT_OPTION(PROTEAN3D_EXAMPLES "Build examples" ON "\"\${PROTEAN3D_GL_CONTEXT}\"  STREQUAL \"Qt\"" OFF)

if (PROTEAN3D_EXAMPLES)
  add_subdirectory(examples)
endif()


