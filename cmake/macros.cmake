# get list of sub-directories
macro(TRAITS3D_SUBDIRLIST result srcdir)
  file(GLOB children RELATIVE ${srcdir} ${srcdir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${srcdir}/${child})
        SET(dirlist ${dirlist} ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

macro(TRAITS3D_WRITE_GL_CONFIGURATION headerlist)
  SET(TRAITS3D_GL_CONFIG_FILE ${PROJECT_BINARY_DIR}/generated_headers/gl_includes.h)
  file(WRITE ${TRAITS3D_GL_CONFIG_FILE}  "// GENERATED FILE - DON'T TOUCH!\n" )
  file(APPEND ${TRAITS3D_GL_CONFIG_FILE} "#pragma once\n\n" )
  foreach(header ${headerlist})
    file(APPEND ${TRAITS3D_GL_CONFIG_FILE}  "#include <${header}>\n" )
  endforeach()
endmacro()
