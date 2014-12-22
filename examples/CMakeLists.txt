if ("${PROTEAN3D_EXAMPLES_GL_CONTEXT}"  STREQUAL "Qt")
    add_subdirectory(qt)
elseif ("${PROTEAN3D_EXAMPLES_GL_CONTEXT}"  STREQUAL "GLFW") 
    add_subdirectory(glfw)
endif()

