system("qmake -project -nopwd -r . ../_common -o simpleplot.pri")
include(simpleplot.pri)
include(../common.pro)

QT       += core gui widgets

TARGET = simpleplot
TEMPLATE = app

