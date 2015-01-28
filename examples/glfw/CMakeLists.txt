CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

set (GLFW_BUILD_EXAMPLES OFF)
set (GLFW_BUILD_TESTS OFF)
set (GLFW_BUILD_DOCS OFF)

set (PROTEAN3D_GLFW_VERSION "3.1")
include_directories(_common)
include_directories(_common/glfw-${PROTEAN3D_GLFW_VERSION}/include)

add_subdirectory(_common)
file(GLOB PROTEAN3D_GL_DIR_SOURCES ${PROTEAN3D_GL_DIR}/*.*)
add_library(glloader_glfw STATIC ${PROTEAN3D_GL_DIR_SOURCES})
set_property(TARGET glloader_glfw PROPERTY FOLDER "examples/glfw/common")

# not before this point
add_definitions(-DGLFW_INCLUDE_NONE)

# real examples

add_definitions(-DPROTEAN3D_DLL)
PROTEAN3D_SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

# no executables to create here
list(REMOVE_ITEM SUBDIRS _common)

list (APPEND MY_LINK_LIBRARIES protean3d ${OPENGL_LIBRARIES} window)

# create single project for every example 
#(needs this strange syntax to expand lists correctly in cmake function)
protean3d_example_creator("${SUBDIRS}" "${MY_LINK_LIBRARIES}" "examples/glfw")



