if ("${PROTEAN3D_VARIANT_GLVARIANT}"  STREQUAL "glload")
  #add_subdirectory(opengl/glload)
  FILE(GLOB PROTEAN3D_GL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/opengl/glload/gl_core_3*.*)  
elseif ("${PROTEAN3D_VARIANT_GLVARIANT}"  STREQUAL "glew") 
  add_subdirectory(opengl/glew)
endif()

set (PROTEAN3D_GL_SOURCES ${PROTEAN3D_GL_SOURCES} PARENT_SCOPE)
