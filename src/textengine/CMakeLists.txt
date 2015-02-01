add_subdirectory(stb)
include_directories(stb/include)

file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS include/protean3d/textengine/*.h)

# make source group for VS etc.; won't work below this level
file(GLOB  GENERATED include/protean3d/textengine/*generated* *generated*)
source_group(generated FILES ${GENERATED})

include_directories(include)
set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/stb/OpenSans_Regular.cpp PROPERTIES GENERATED TRUE)
add_library(textengine STATIC ${CMAKE_CURRENT_SOURCE_DIR}/stb/OpenSans_Regular.cpp ${SOURCES} ${HEADERS})
add_dependencies(textengine create_fonts_target)
