file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS include/protean3d/glbase/*.h)

add_library(glbase STATIC ${SOURCES} ${HEADERS})
