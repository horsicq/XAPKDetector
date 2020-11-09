QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xad
TEMPLATE = app

include(../build.pri)
XCONFIG += use_dex
XCONFIG += use_archive

SOURCES +=\
        guimainwindow.cpp \
    dialogabout.cpp \
    main_gui.cpp \
    dialogoptions.cpp

HEADERS  += guimainwindow.h \
    ../global.h \
    dialogabout.h \
    dialogoptions.h

FORMS    += guimainwindow.ui \
    dialogabout.ui \
    dialogoptions.ui \
    dialogdirectoryscan.ui


!contains(XCONFIG, archive_widget) {
    XCONFIG += archive_widget
    include(../archive_widget/archive_widget.pri)
}

!contains(XCONFIG, formresult) {
    XCONFIG += formresult
    include(../StaticScan/formresult.pri)
}

!contains(XCONFIG, allformatwidgets) {
    XCONFIG += allformatwidgets
    include(../FormatWidgets/allformatwidgets.pri)
}

!contains(XCONFIG, dexwidget) {
    XCONFIG += dexwidget
    include(../FormatWidgets/DEX/dexwidget.pri)
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
