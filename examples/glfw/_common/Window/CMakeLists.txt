add_definitions(-DEXAMPLE_DLL -DEXAMPLE_MAKEDLL)

file(GLOB  SOURCES *.c*)
file(GLOB  HEADERS *.h)
add_library(window SHARED ${SOURCES} ${HEADERS})
target_link_libraries(window glfw ${GLFW_LIBRARIES})
target_link_libraries(window)
