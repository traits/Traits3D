add_definitions(-DPROTEAN3D_DLL -DPROTEAN3D_MAKEDLL)

find_package(OpenGL REQUIRED)
list(APPEND ALL_LIBS ${OPENGL_LIBRARY})

#adding OpenGL sources
add_subdirectory(3rdparty)
# Unresolved stuff from '3rdparty' dir
# A nuisance, having to do this here 
include_directories(3rdparty/glm)
SOURCE_GROUP(GL FILES ${PROTEAN3D_GL_SOURCES})
if ("${PROTEAN3D_VARIANT_GLVARIANT}"  STREQUAL "glload")
  include_directories(3rdparty/opengl/glload)
elseif ("${PROTEAN3D_VARIANT_GLVARIANT}"  STREQUAL "glew") 
  include_directories(3rdparty/opengl/glew)
endif()

# adding core sources
add_subdirectory(protean3d)


add_library(protean3d SHARED ${PROTEAN3D_GL_SOURCES} ${PROTEAN3D_CORE_SOURCES} ${PROTEAN3D_CORE_HEADERS})
target_link_libraries(protean3d ${ALL_LIBS})

