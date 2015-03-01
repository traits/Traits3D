system("qmake -project -nopwd -r . ../_common -o mesh.pri")
include(mesh.pri)
include(../common.pro)

QT       += core gui widgets

TARGET = mesh
TEMPLATE = app

android{
color_files.files = ../resources/colormaps
color_files.path = $$[PWD]/assets
INSTALLS += color_files
}

