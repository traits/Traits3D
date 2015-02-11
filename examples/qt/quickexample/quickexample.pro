system("qmake -project -nopwd -r . ../_common -o quickexample.pri")
include(quickexample.pri)
include(../common.pro)

QT       += qml quick
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quickexample
TEMPLATE = app

OTHER_FILES += \
    main.qml
  
