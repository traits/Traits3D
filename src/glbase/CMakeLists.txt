file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS protean3d/glbase/*.h)

add_library(glbase STATIC ${SOURCES} ${HEADERS})
