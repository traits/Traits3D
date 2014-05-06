# Find GLESv3
#
# GLESv3_INCLUDE_DIR
# GLESv3_LIBRARY
# GLESV3_FOUND   !!! note the uppercase

find_path(GLESv3_INCLUDE_DIR NAMES GLES3/gl3.h)

set(GLESv3_NAMES ${GLESv3_NAMES} libGLESv2)

find_library(GLESv3_LIBRARY 
  NAMES ${GLESv3_NAMES}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLESv3 DEFAULT_MSG GLESv3_LIBRARY GLESv3_INCLUDE_DIR)

mark_as_advanced(GLESv3_INCLUDE_DIR GLESv3_LIBRARY)

if(GLESV3_FOUND)
    set(GLESv3_INCLUDE_DIRS ${GLESv3_INCLUDE_DIR})
    set(GLESv3_LIBRARIES ${GLESv3_LIBRARY})
endif()

