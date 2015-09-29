CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

set (TRAITS3D_GLFW_VERSION "3.1.1")
include_directories(_common)
include_directories(_common/glfw-${TRAITS3D_GLFW_VERSION}/include)
add_subdirectory(_common)

# not before this point
add_definitions(-DGLFW_INCLUDE_NONE)

# real examples

add_definitions(-DTRAITS3D_DLL)
TRAITS3D_SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

# no executables to create here
list(REMOVE_ITEM SUBDIRS _common)

list (APPEND MY_LINK_LIBRARIES traits3d ${OPENGL_LIBRARIES} window)

# create single project for every example 
#(needs this strange syntax to expand lists correctly in cmake function)
example_creator("${SUBDIRS}" "${MY_LINK_LIBRARIES}" "examples/glfw")



