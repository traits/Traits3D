add_subdirectory(stb)
include_directories(stb/include)

file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS include/protean3d/textengine/*.h)

include_directories(include)
add_library(textengine STATIC ${SOURCES} ${HEADERS})
set_property(TARGET textengine PROPERTY FOLDER "textengine")
