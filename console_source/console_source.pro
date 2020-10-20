QT += core
QT -= gui

include(../build.pri)
XCONFIG += use_dex

CONFIG += c++11

TARGET = xadc
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main_console.cpp

!contains(XCONFIG, staticscan) {
    XCONFIG += staticscan
    include(../StaticScan/staticscan.pri)
}
