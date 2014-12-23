CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

add_subdirectory(glfw-3.0.4)

# set and hide some GLFW specific variables
set(USE_MSVC_RUNTIME_LIBRARY_DLL ON)
mark_as_advanced(USE_MSVC_RUNTIME_LIBRARY_DLL)
set(GLFW_INSTALL OFF)
mark_as_advanced(GLFW_INSTALL)
mark_as_advanced(GLFW_USE_DWM_SWAP_INTERVAL )
mark_as_advanced(GLFW_USE_OPTIMUS_HPG)
mark_as_advanced(GLFW_USE_EGL)
#    set(EXTERNAL_INCLUDE_PATH "V:/include")
#    set(EXTERNAL_LIBRARY_PATH "V:/lib")

#    # for find_package
#    list(APPEND CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${EXTERNAL_INCLUDE_PATH}/glfw)
#    list(APPEND CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${EXTERNAL_LIBRARY_PATH}/glfw)

#    find_package(GLFW REQUIRED)
#    if (GLFW_FOUND)
#      include_directories(${GLFW_INCLUDE_DIRS})
#      list(APPEND ALL_LIBS ${GLFW_LIBRARIES})
#    endif (GLFW_FOUND) 

add_subdirectory(Window)
set_property(TARGET glfw PROPERTY FOLDER "examples/glfw/common")
set_property(TARGET window PROPERTY FOLDER "examples/glfw/common")




