system("qmake -project -nopwd -r . ../_common -o simpleplot.pri")
include(simpleplot.pri)
include(../common.pro)

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simpleplot
TEMPLATE = app

