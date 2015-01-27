create_resources("fonts" "fonts_stb_generated")

file(GLOB  SOURCES *.cpp)
file(GLOB  HEADERS *.h)

add_library(fontprovider_stb STATIC ${SOURCES} ${HEADERS})
set_property(TARGET fontprovider_stb PROPERTY FOLDER "fontprovider/stb")
