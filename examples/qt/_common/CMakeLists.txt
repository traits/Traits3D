add_definitions(-DEXAMPLE_DLL -DEXAMPLE_MAKEDLL)

file(GLOB  SOURCES *.c*)
file(GLOB  HEADERS *.h*)

add_library(qtwidget SHARED ${SOURCES} ${HEADERS})
target_link_libraries(qtwidget traits3d Qt5::Widgets Qt5::OpenGL)
