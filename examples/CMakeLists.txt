include_directories(${PROJECT_SOURCE_DIR}/src/3rdparty)
include_directories(${PROJECT_SOURCE_DIR}/src/base/include)
include_directories(${PROJECT_SOURCE_DIR}/src/glbase/include)
include_directories(${PROJECT_SOURCE_DIR}/src/traits3d/include)
include_directories(${PROJECT_SOURCE_DIR}/src/textengine/include)

if (TRAITS3D_EXAMPLES_QT)
    add_subdirectory(qt)
endif()
if (TRAITS3D_EXAMPLES_GLFW)
    add_subdirectory(glfw)
endif()

