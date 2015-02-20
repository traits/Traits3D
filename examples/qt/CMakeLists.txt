CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

set(QT5CMAKEROOT "v:/lib/qt/qt5/install/x64/lib/cmake" CACHE STRING "Qt cmake root")
#set(QT5CMAKEROOT "v:/lib/qt/qt5/install/android/x86/lib/cmake" CACHE STRING "Qt cmake root")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(Qt5Quick)
# add_definitions(-DPROTEAN3D_QT_LABEL)
# add_subdirectory(src/platform/qt)
#set(QT_USE_QTOPENGL TRUE)


include_directories(_common)
add_subdirectory(_common)
set_property(TARGET qtwidget PROPERTY FOLDER "examples/qt/common")

# real examples

add_definitions(-DPROTEAN3D_DLL)
PROTEAN3D_SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

# no executables to create here
list(REMOVE_ITEM SUBDIRS _common)

list (APPEND MY_LINK_LIBRARIES protean3d ${OPENGL_LIBRARIES} Qt5::Widgets Qt5::Quick qtwidget)

# create single project for every example 
#(needs this strange syntax to expand lists correctly in cmake function)
protean3d_example_creator("${SUBDIRS}" "${MY_LINK_LIBRARIES}" "examples/qt")


