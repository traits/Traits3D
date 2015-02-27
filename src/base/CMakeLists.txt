file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS include/traits3d/*.h)

include_directories(include)
add_library(base STATIC ${SOURCES} ${HEADERS})
