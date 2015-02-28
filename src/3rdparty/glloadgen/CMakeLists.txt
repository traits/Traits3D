if ("${TRAITS3D_GL_VARIANT}"  STREQUAL "OPENGL")
  if ("${TRAITS3D_GL_MAJOR}"  GREATER 3)
    set(TRAITS3D_GL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GL_4_2 CACHE INTERNAL "OpenGL interface files" FORCE)
  else()
    set(TRAITS3D_GL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GL_3_3 CACHE INTERNAL "OpenGL interface files" FORCE)  
  endif()
  file(GLOB SOURCES ${TRAITS3D_GL_DIR}/*.c)    
elseif ("${TRAITS3D_GL_VARIANT}"  STREQUAL "OPENGL_ES")
  # ES sources  
endif()

include_directories(${TRAITS3D_GL_DIR}/include/traits3d/opengl)
add_library(glimpl STATIC ${SOURCES})
