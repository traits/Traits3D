add_subdirectory(stb)
include_directories(stb/include)

file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS include/protean3d/textengine/*.h)

# make source group for VS etc.; won't work below this level
file(GLOB  GENERATED include/protean3d/textengine/*generated* *generated*)
source_group(generated FILES ${GENERATED})

include_directories(include)
add_library(textengine STATIC ${SOURCES} ${HEADERS})
