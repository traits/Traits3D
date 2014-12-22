add_definitions(-DEXAMPLE_DLL -DEXAMPLE_MAKEDLL)

include_directories(../glfw-3.0.4/include)

file(GLOB  SOURCES *.c*)
file(GLOB  HEADERS *.h)
add_library(window SHARED ${SOURCES} ${HEADERS})
target_link_libraries(window glfw ${GLFW_LIBRARIES})
