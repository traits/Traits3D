create_resources("fonts" 
    "${PROJECT_SOURCE_DIR}/src/textengine" 
    "${PROJECT_SOURCE_DIR}/src/textengine/include/protean3d/textengine"
    "fonts_stb_generated"
    "protean3d/textengine")

include_directories(tclap/include)
add_executable(create_fonts create_fonts.cpp)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/OpenSans_Regular.cpp
  COMMAND create_fonts -i "fonts/OpenSans-Regular.ttf" -o "${CMAKE_CURRENT_SOURCE_DIR}/OpenSans_Regular" -t "OpenSans-Regular"
  DEPENDS fonts/OpenSans-Regular.ttf)

add_custom_target (create_fonts_target DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/OpenSans_Regular.cpp)  
