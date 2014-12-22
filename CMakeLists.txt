CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

# http://www.volumesoffun.com/tag/cmake/
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

PROJECT("Protean3D")
set(CMAKE_DEBUG_POSTFIX "D")

include("CMakeDependentOption")
include("cmake/macros.cmake")

# search local cmake stuff
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Build & Install directories
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/../install CACHE PATH "Install directory" FORCE)

# Set dedicated output directory, so we have all the libs/dll's and executables gathered at one place for debugging
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# initialize with true
option(BUILD_SHARED_LIBS "Build shared libraries" ON)


# Target OS
set(PROTEAN3D_OS "Windows" CACHE STRING "Target OS")
set_property(CACHE PROTEAN3D_OS PROPERTY STRINGS "Windows")
#MB todo set_property(CACHE PROTEAN3D_OS PROPERTY STRINGS "Windows" "Linux" "Android" "iOS" "emscripten")

# OpenGL Context Provider
set(PROTEAN3D_EXAMPLES_GL_CONTEXT "GLFW" CACHE STRING "OpenGL Context Provider")
set_property(CACHE PROTEAN3D_EXAMPLES_GL_CONTEXT PROPERTY STRINGS "Qt" "GLFW")

# OpenGL Version Provider
set(PROTEAN3D_GL_VARIANT "OPENGL" CACHE STRING "OpenGL Variant (OpenGL, OpenGL ES, WebGL)")
set_property(CACHE PROTEAN3D_GL_VARIANT PROPERTY STRINGS "OPENGL" "OPENGL_ES" "WEBGL")

# Font Provider
set(PROTEAN3D_TEXT "Core" CACHE STRING "Font/String Provider")
set_property(CACHE PROTEAN3D_TEXT PROPERTY STRINGS "Core" "freetype" "Qt")

add_subdirectory(src)

option(TARGET_GLES "Build for OpenGL ES instead of desktop OpenGL" OFF)
CMAKE_DEPENDENT_OPTION(TARGET_GLES2 "Build for OpenGL ES 2" ON "TARGET_GLES" OFF)
CMAKE_DEPENDENT_OPTION(TARGET_DESKTOP_GLES "Build for OpenGL ES on desktop" OFF "TARGET_GLES" OFF)



option(PROTEAN3D_EXAMPLES "Build examples" ON)
# CMAKE_DEPENDENT_OPTION(PROTEAN3D_EXAMPLES "Build examples" ON "\"\${PROTEAN3D_EXAMPLES_GL_CONTEXT}\"  STREQUAL \"Qt\"" OFF)

#MB todo
# set(PROTEAN3D_GL_HEADER_PATH "" CACHE PATH "OpenGL header root")
# set(PROTEAN3D_GL_HEADERS "EGL/h0.h" "h1.h" CACHE STRING "OpenGL headers")
# set(PROTEAN3D_GL_SOURCES "" CACHE FILEPATH "OpenGL sources")
# set(PROTEAN3D_GL_LIBRARIES "h0.lib" "h1.lib" CACHE STRING "OpenGL libraries")
# set(PROTEAN3D_GL_LIBRARY_PATH "" CACHE PATH "OpenGL library root")
# PROTEAN3D_WRITE_GL_CONFIGURATION("${PROTEAN3D_GL_HEADERS}")

if (PROTEAN3D_EXAMPLES)
  add_subdirectory(examples)
endif()


