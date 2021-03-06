#CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++1y  -O0
DEFINES += TRAITS3D_GL_IS_OPENGL_ES
#todo!
DEFINES += QT_OPENGL_ES_3 # GL_ES_VERSION_3_0
CONFIG += mobility
MOBILITY = 

INCLUDEPATH += \
    ../../../src/3rdparty \
    ../../../src/base/include \
    ../../../src/glbase/include \
    ../../../src/traits3d/include \
    ../../../src/textengine/include \
    ../../../src/textengine/fontlib\include \
    ../_common

LIBS += -lGLESv3 -L$$OUT_PWD/../../../src -ltraits3d
