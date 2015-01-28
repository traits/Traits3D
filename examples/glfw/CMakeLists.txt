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
foreach(subdir ${SUBDIRS})
  file(GLOB  ${subdir}_SOURCES ${subdir}/*.c*)
  file(GLOB  ${subdir}_HEADERS ${subdir}/*.h)
  
  add_executable(${subdir}  ${${subdir}_SOURCES} ${${subdir}_HEADERS})
  set_property(TARGET ${subdir} PROPERTY FOLDER "examples/glfw")

  target_link_libraries(${subdir} ${MY_LINK_LIBRARIES})
  set_target_properties(${subdir} PROPERTIES WIN32_EXECUTABLE false)
  install(TARGETS ${subdir} 
    RUNTIME DESTINATION bin 
    LIBRARY DESTINATION bin 
    ARCHIVE DESTINATION lib
    )
endforeach()


