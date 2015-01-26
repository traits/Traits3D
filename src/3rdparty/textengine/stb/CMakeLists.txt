create_resources("fonts" "fonts_std_generated")

file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS *.h)

add_library(textengine_stb STATIC ${SOURCES} ${HEADERS})
