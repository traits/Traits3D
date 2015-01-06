add_definitions(-DEXAMPLE_DLL -DEXAMPLE_MAKEDLL)

include_directories(../../../src)
include_directories(../../../src/3rdparty)

file(GLOB  SOURCES *.c*)
file(GLOB  HEADERS *.h*)

file(GLOB PROTEAN3D_GL_DIR_SOURCES ${PROTEAN3D_GL_DIR}/*.*)
add_library(glloader_qt STATIC ${PROTEAN3D_GL_DIR_SOURCES})
set_property(TARGET glloader_qt PROPERTY FOLDER "examples/qt/common")

add_library(qtwidget SHARED ${SOURCES} ${HEADERS})
target_link_libraries(qtwidget protean3d glloader_qt Qt5::Widgets Qt5::OpenGL)
