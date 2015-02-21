add_definitions(-DEXAMPLE_DLL -DEXAMPLE_MAKEDLL)

file(GLOB  SOURCES *.c*)
file(GLOB  HEADERS *.h*)

file(GLOB TRAITS3D_GL_DIR_SOURCES ${TRAITS3D_GL_DIR}/*.*)
add_library(glloader_qt STATIC ${TRAITS3D_GL_DIR_SOURCES})
set_property(TARGET glloader_qt PROPERTY FOLDER "examples/qt/common")

add_library(qtwidget SHARED ${SOURCES} ${HEADERS})
target_link_libraries(qtwidget traits3d glloader_qt Qt5::Widgets Qt5::OpenGL)
