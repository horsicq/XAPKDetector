QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nfd
TEMPLATE = app

include(../build.pri)

SOURCES +=\
        guimainwindow.cpp \
    dialogabout.cpp \
    main_gui.cpp \
    dialogoptions.cpp \
    dialogdirectoryscan.cpp

HEADERS  += guimainwindow.h \
    ../global.h \
    dialogabout.h \
    dialogoptions.h \
    dialogdirectoryscan.h

FORMS    += guimainwindow.ui \
    dialogabout.ui \
    dialogoptions.ui \
    dialogdirectoryscan.ui


!contains(XCONFIG, formresult) {
    XCONFIG += formresult
    include(../StaticScan/formresult.pri)
}

!contains(XCONFIG, xoptions) {
    XCONFIG += xoptions
    include(../XOptions/xoptions.pri)
}

win32 {
    RC_ICONS = ../icons/main.ico
}

macx {
    ICON = ../icons/main.icns
}

RESOURCES += \
    resources.qrc
