CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)

if ("${PROTEAN3D_EXAMPLES_GL_CONTEXT}"  STREQUAL "Qt")
  # add_subdirectory(src/platform/qt)
  set(QT_USE_QTOPENGL TRUE)
  find_package(Qt4 4.8 REQUIRED)
  include(UseQt4)
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
  # add_definitions(-DPROTEAN3D_QT_LABEL)
elseif ("${PROTEAN3D_EXAMPLES_GL_CONTEXT}"  STREQUAL "GLFW") 
  add_subdirectory(glfw-3.0.4)
  include_directories(glfw-3.0.4/include)
  add_definitions(-DGLFW_INCLUDE_NONE)
#    set(EXTERNAL_INCLUDE_PATH "V:/include")
#    set(EXTERNAL_LIBRARY_PATH "V:/lib")

#    # for find_package
#    list(APPEND CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${EXTERNAL_INCLUDE_PATH}/glfw)
#    list(APPEND CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${EXTERNAL_LIBRARY_PATH}/glfw)

#    find_package(GLFW REQUIRED)
#    if (GLFW_FOUND)
#      include_directories(${GLFW_INCLUDE_DIRS})
#      list(APPEND ALL_LIBS ${GLFW_LIBRARIES})
#    endif (GLFW_FOUND) 
endif()


# real examples

#add_definitions(-DGLFW_DLL)
add_definitions(-DPROTEAN3D_DLL)

PROTEAN3D_SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

# no executables to create here
list(REMOVE_ITEM SUBDIRS glfw-3.0.4)


file(GLOB PROTEAN3D_GL_DIR_SOURCES ${PROTEAN3D_GL_DIR}/*.*)
add_library(glloader STATIC ${PROTEAN3D_GL_DIR_SOURCES})

# create single project for every example
foreach(subdir ${SUBDIRS})
  file(GLOB  ${subdir}_PROTEAN3D_EXAMPLE_SOURCES ${subdir}/*.c*)
  file(GLOB  ${subdir}_PROTEAN3D_EXAMPLE_HEADERS ${subdir}/*.h)

  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/3rdparty)
  #include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/3rdparty/glloadgen/${PROTEAN3D_GL_VERSION})

  include_directories(${CMAKE_SOURCE_DIR}/src)
  add_executable(${subdir}  ${${subdir}_PROTEAN3D_EXAMPLE_SOURCES} ${${subdir}_PROTEAN3D_EXAMPLE_HEADERS})
  target_link_libraries(${subdir} protean3d ${OPENGL_LIBRARIES})
  target_link_libraries(${subdir} glloader)
  target_link_libraries(${subdir} glfw ${GLFW_LIBRARIES})
  set_target_properties(${subdir} PROPERTIES WIN32_EXECUTABLE false)
  install(TARGETS ${subdir} 
    RUNTIME DESTINATION bin 
    LIBRARY DESTINATION bin 
    ARCHIVE DESTINATION lib
    )
endforeach()


