add_definitions(-DPROTEAN3D_DLL -DPROTEAN3D_MAKEDLL)

find_package(OpenGL REQUIRED)
list(APPEND ALL_LIBS ${OPENGL_LIBRARY})
# include_directories(../include ../include/3thparty)

file(GLOB  PROTEAN3D_CORE_SOURCES *.cpp)
file(GLOB  PROTEAN3D_CORE_HEADERS *.h)

set(PROTEAN3D_SOURCES ${PROTEAN3D_CORE_SOURCES})
set(PROTEAN3D_HEADERS ${PROTEAN3D_CORE_HEADERS})

add_library(protean3d SHARED ${PROTEAN3D_SOURCES} ${PROTEAN3D_HEADERS})
target_link_libraries(protean3d ${ALL_LIBS})
