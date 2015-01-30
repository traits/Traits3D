add_subdirectory(stb)

file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS include/protean3d/textengine/*.h)

include_directories(include)
add_library(textengine STATIC ${SOURCES} ${HEADERS})
