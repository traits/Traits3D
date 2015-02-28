system("qmake -project -nopwd -r . ../_common -o mesh.pri")
include(mesh.pri)
include(../common.pro)

QT       += core gui widgets

TARGET = mesh
TEMPLATE = app

