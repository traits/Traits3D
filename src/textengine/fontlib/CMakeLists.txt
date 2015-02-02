file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS include/protean3d/fonts/*.h)

include_directories(include)
add_library(fontlib STATIC ${SOURCES} ${HEADERS})

set_property(TARGET fontlib PROPERTY FOLDER "textengine")
