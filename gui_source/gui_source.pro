QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nfd
TEMPLATE = app

include(../build.pri)

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
    include(../../_mylibs/archive_widget/archive_widget.pri)
}

!contains(XCONFIG, nfd_widget) {
    XCONFIG += nfd_widget
    include(../../_mylibs/nfd_widget/nfd_widget.pri)
}

!contains(XCONFIG, allformatwidgets) {
    XCONFIG += allformatwidgets
    include(../../_mylibs/FormatWidgets/allformatwidgets.pri)
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
