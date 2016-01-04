file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS include/glb/*.h)

include_directories(include)
add_library(glbase STATIC ${SOURCES} ${HEADERS})
