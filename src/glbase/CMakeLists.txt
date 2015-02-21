file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS include/traits3d/glbase/*.h)

include_directories(include)
add_library(glbase STATIC ${SOURCES} ${HEADERS})
