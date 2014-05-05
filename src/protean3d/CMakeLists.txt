file(GLOB  PROTEAN3D_CORE_SOURCES *.cpp)
file(GLOB  PROTEAN3D_CORE_HEADERS *.h)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_includes.h.in
    ${PROJECT_BINARY_DIR}/generated_headers/gl_includes.h
)
include_directories(${PROJECT_BINARY_DIR}/generated_headers)

set (PROTEAN3D_CORE_SOURCES ${PROTEAN3D_CORE_SOURCES} PARENT_SCOPE)
set (PROTEAN3D_CORE_HEADERS ${PROTEAN3D_CORE_HEADERS} PARENT_SCOPE)
