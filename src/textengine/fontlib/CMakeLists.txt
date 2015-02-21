file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS include/traits3d/fonts/*.h)

include_directories(include)
add_library(fontlib STATIC ${SOURCES} ${HEADERS})

set_property(TARGET fontlib PROPERTY FOLDER "textengine")
