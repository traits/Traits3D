file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS include/protean3d/textengine/*.h)

add_subdirectory(3rdparty)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
add_library(textengines STATIC ${SOURCES} ${HEADERS})
