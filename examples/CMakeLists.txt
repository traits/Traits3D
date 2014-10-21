CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

add_subdirectory(_common)

# real examples

#add_definitions(-DGLFW_DLL)
add_definitions(-DPROTEAN3D_DLL)

PROTEAN3D_SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

# no executables to create here
list(REMOVE_ITEM SUBDIRS _common)

file(GLOB PROTEAN3D_GL_DIR_SOURCES ${PROTEAN3D_GL_DIR}/*.*)
add_library(glloader STATIC ${PROTEAN3D_GL_DIR_SOURCES})

# create single project for every example
foreach(subdir ${SUBDIRS})
  file(GLOB  ${subdir}_PROTEAN3D_EXAMPLE_SOURCES ${subdir}/*.c*)
  file(GLOB  ${subdir}_PROTEAN3D_EXAMPLE_HEADERS ${subdir}/*.h)

  add_definitions(-DGLFW_INCLUDE_NONE)
  include_directories(_common)
  include_directories(_common/glfw-3.0.4/include)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/3rdparty)
  #include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/3rdparty/glloadgen/${PROTEAN3D_GL_VERSION})

  include_directories(${CMAKE_SOURCE_DIR}/src)
  add_executable(${subdir}  ${${subdir}_PROTEAN3D_EXAMPLE_SOURCES} ${${subdir}_PROTEAN3D_EXAMPLE_HEADERS})
  target_link_libraries(${subdir} protean3d ${OPENGL_LIBRARIES})
  target_link_libraries(${subdir} glloader)
  #target_link_libraries(${subdir} glfw ${GLFW_LIBRARIES})
  target_link_libraries(${subdir} window)
  set_target_properties(${subdir} PROPERTIES WIN32_EXECUTABLE false)
  install(TARGETS ${subdir} 
    RUNTIME DESTINATION bin 
    LIBRARY DESTINATION bin 
    ARCHIVE DESTINATION lib
    )
endforeach()


