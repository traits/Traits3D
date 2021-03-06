# - Find the OpenGL Extension Wrangler Library (GLFW)
# This module defines the following variables:
#  GLFW_INCLUDE_DIRS - include directories for GLFW
#  GLFW_LIBRARIES - libraries to link against GLFW
#  GLFW_FOUND - true if GLFW has been found and can be used

#=============================================================================
# Copyright 2012 Benjamin Eikel
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

find_path(GLFW_INCLUDE_DIR GL/glfw.h)
find_library(GLFW_LIBRARY NAMES glfw PATH_SUFFIXES lib64)

set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
set(GLFW_LIBRARIES ${GLFW_LIBRARY})

include(${CMAKE_ROOT}/modules/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(GLFW
                                  REQUIRED_VARS GLFW_INCLUDE_DIR GLFW_LIBRARY)

mark_as_advanced(GLFW_INCLUDE_DIR GLFW_LIBRARY)
