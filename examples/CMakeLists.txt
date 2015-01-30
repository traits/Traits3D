include_directories(${PROJECT_SOURCE_DIR}/src/3rdparty)
include_directories(${PROJECT_SOURCE_DIR}/src/glbase/include)
include_directories(${PROJECT_SOURCE_DIR}/src/protean3d/include)
include_directories(${PROJECT_SOURCE_DIR}/src/textengines/include)

if (PROTEAN3D_EXAMPLES_QT)
    add_subdirectory(qt)
endif()
if (PROTEAN3D_EXAMPLES_GLFW)
    add_subdirectory(glfw)
endif()

