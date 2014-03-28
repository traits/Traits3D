CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)

if ("${PROTEAN3D_VARIANT_CONTEXT}"  STREQUAL "Qt")
  # add_subdirectory(src/platform/qt)
  set(QT_USE_QTOPENGL TRUE)
  find_package(Qt4 4.8 REQUIRED)
  include(UseQt4)
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
  # add_definitions(-DPROTEAN3D_QT_LABEL)
elseif ("${PROTEAN3D_VARIANT_CONTEXT}"  STREQUAL "GLFW") 
  add_subdirectory(glfw-3.0.4)
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


