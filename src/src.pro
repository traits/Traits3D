system("qmake -project -nopwd -r . -o src.pri")

include(src.pri)

QT       += core gui widgets

#CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++1y -O0 -fno-strict-aliasing

TARGET = traits3d
TEMPLATE = lib
DEFINES += TRAITS3D_GL_IS_OPENGL_ES
#todo!
DEFINES += QT_OPENGL_ES_3 GL_ES_VERSION_3_0
LIBS += -lGLESv3


INCLUDEPATH += \
    3rdparty \
    base/include \
    glbase/include \
    traits3d/include \
    textengine/include \
    textengine/fontlib\include 

SOURCES -= 3rdparty/glloadgen/GL_3_3/gl_core_3_3.c \
           3rdparty/glloadgen/GL_4_2/gl_core_4_2.c \
           3rdparty/glm/detail/dummy.cpp
           
HEADERS -= 3rdparty/glloadgen/GL_3_3/gl_core_3_3.h \
           3rdparty/glloadgen/GL_4_2/gl_core_4_2.h
    
CONFIG += mobility debug
MOBILITY = 
