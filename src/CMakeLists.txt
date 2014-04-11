add_definitions(-DPROTEAN3D_DLL -DPROTEAN3D_MAKEDLL)
add_definitions(-DPROTEAN3D_GL_IS_${PROTEAN3D_GL_VARIANT})
add_definitions(-DPROTEAN3D_GL_VERSION_MAJOR=${PROTEAN3D_GL_VERSION_MAJOR})
add_definitions(-DPROTEAN3D_GL_VERSION_MINOR=${PROTEAN3D_GL_VERSION_MINOR})

find_package(OpenGL REQUIRED)
list(APPEND ALL_LIBS ${OPENGL_LIBRARY})

#adding OpenGL sources
add_subdirectory(3rdparty)
# Unresolved stuff from '3rdparty' dir
# A nuisance, having to do this here 
include_directories(3rdparty)
SOURCE_GROUP(GL FILES ${PROTEAN3D_GL_SOURCES})

include_directories(${PROTEAN3D_GL_DIR})

# adding core sources
add_subdirectory(protean3d)


add_library(protean3d SHARED ${PROTEAN3D_GL_SOURCES} ${PROTEAN3D_CORE_SOURCES} ${PROTEAN3D_CORE_HEADERS})
target_link_libraries(protean3d ${ALL_LIBS})

