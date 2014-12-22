add_definitions(-DEXAMPLE_DLL -DEXAMPLE_MAKEDLL)

include_directories(../../../src)
include_directories(../../../src/3rdparty)

file(GLOB  SOURCES *.c*)
file(GLOB  HEADERS *.h*)
add_library(qtwidget SHARED ${SOURCES} ${HEADERS})
target_link_libraries(qtwidget protean3d)
target_link_libraries(qtwidget Qt5::Widgets Qt5::OpenGL)
