CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

set(QT5CMAKEROOT "v:/lib/qt/qt5/install/x64/lib/cmake" CACHE STRING "Qt cmake root")
set(Qt5Widgets_DIR "${QT5CMAKEROOT}/Qt5Widgets" CACHE STRING "Qt Widgets")
set(Qt5OpenGL_DIR "${QT5CMAKEROOT}/Qt5OpenGL" CACHE STRING "Qt OpenGL support")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
# add_definitions(-DPROTEAN3D_QT_LABEL)
# add_subdirectory(src/platform/qt)
#set(QT_USE_QTOPENGL TRUE)


add_subdirectory(_common)
set_property(TARGET qtwidget PROPERTY FOLDER "examples/qt/qtwidget")

# real examples

##add_definitions(-DGLFW_DLL)
add_definitions(-DPROTEAN3D_DLL)

PROTEAN3D_SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
# no executables to create here
list(REMOVE_ITEM SUBDIRS _common)

## no executables to create here
#list(REMOVE_ITEM SUBDIRS _common)

file(GLOB PROTEAN3D_GL_DIR_SOURCES ${PROTEAN3D_GL_DIR}/*.*)
#add_library(glloader STATIC ${PROTEAN3D_GL_DIR_SOURCES})

# create single project for every example
foreach(subdir ${SUBDIRS})
  file(GLOB  ${subdir}_PROTEAN3D_EXAMPLE_SOURCES ${subdir}/*.c*)
  file(GLOB  ${subdir}_PROTEAN3D_EXAMPLE_HEADERS ${subdir}/*.h)

  #add_definitions(-DGLFW_INCLUDE_NONE)
  include_directories(_common)
  #include_directories(_common/glfw-3.0.4/include)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src/3rdparty)
  #include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/3rdparty/glloadgen/${PROTEAN3D_GL_VERSION})

  include_directories(${CMAKE_SOURCE_DIR}/src)
  add_executable(${subdir}  ${${subdir}_PROTEAN3D_EXAMPLE_SOURCES} ${${subdir}_PROTEAN3D_EXAMPLE_HEADERS})
  set_property(TARGET ${subdir} PROPERTY FOLDER "examples/qt/${subdir}")
  target_link_libraries(${subdir} protean3d ${OPENGL_LIBRARIES} Qt5::Widgets)
  #target_link_libraries(${subdir} glloader)
  #target_link_libraries(${subdir} glfw ${GLFW_LIBRARIES})
  target_link_libraries(${subdir} qtwidget)
  set_target_properties(${subdir} PROPERTIES WIN32_EXECUTABLE false)
  install(TARGETS ${subdir} 
    RUNTIME DESTINATION bin 
    LIBRARY DESTINATION bin 
    ARCHIVE DESTINATION lib
    )
endforeach()


