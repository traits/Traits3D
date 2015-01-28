add_definitions(-DPROTEAN3D_DLL -DPROTEAN3D_MAKEDLL)
add_definitions(-DPROTEAN3D_GL_IS_${PROTEAN3D_GL_VARIANT})
add_definitions(-DGLM_FORCE_RADIANS)

find_package(OpenGL REQUIRED)
list(APPEND ALL_LIBS ${OPENGL_LIBRARY})


if ("${PROTEAN3D_GL_VARIANT}"  STREQUAL "OPENGL")
  #adding OpenGL sources
  add_subdirectory(3rdparty)
  # Unresolved stuff from '3rdparty' dir
  # A nuisance, having to do this here 
  SOURCE_GROUP(GL FILES ${PROTEAN3D_GL_SOURCES})
  include_directories(${PROTEAN3D_GL_DIR})
elseif ("${PROTEAN3D_GL_VARIANT}"  STREQUAL "OPENGL_ES")
  list(APPEND CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} $ENV{OPENGLES_MALI}/include)
  list(APPEND CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} $ENV{OPENGLES_MALI}/lib)
  find_package(GLESv3 REQUIRED)
  include_directories(${GLESv3_INCLUDE_DIRS})    
  list(APPEND ALL_LIBS ${GLESv3_LIBRARIES})
endif()

# glm and glloadgen files
include_directories(3rdparty)

add_subdirectory(resources)

# gl buffer/shader support classes
add_subdirectory(glbase)
include_directories(glbase)
list(APPEND ALL_LIBS glbase)
include_directories(protean3d/include)

# adding core sources
add_subdirectory(protean3d)

add_library(protean3d SHARED ${PROTEAN3D_GL_SOURCES} ${PROTEAN3D_CORE_SOURCES} ${PROTEAN3D_CORE_HEADERS})
target_link_libraries(protean3d ${ALL_LIBS})

install(TARGETS protean3d 
    RUNTIME DESTINATION bin 
    LIBRARY DESTINATION bin 
    ARCHIVE DESTINATION lib
    )