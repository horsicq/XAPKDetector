QT += core
QT -= gui

XCONFIG += use_dex
XCONFIG += use_archive
XCONFIG += use_pdf

include(../build.pri)

CONFIG += c++11

TARGET = xapkdc
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main_console.cpp

!contains(XCONFIG, specabstract) {
    XCONFIG += specabstract
    include(../../_mylibs/SpecAbstract/specabstract.pri)
}

win32 {
    CONFIG -= embed_manifest_exe
    QMAKE_MANIFEST = windows.manifest.xml
}

DISTFILES += \
    CMakeLists.txt
