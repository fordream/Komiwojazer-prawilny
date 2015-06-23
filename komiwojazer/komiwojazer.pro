#-------------------------------------------------
#
# Project created by QtCreator 2015-04-25T15:54:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET     = komiproj
QMAKE_PROJECT_NAME = Komiwojazer
win32 {
    CONFIG(debug, release|debug):DESTDIR = ../debug/
    CONFIG(release, release|debug):DESTDIR = ../release/
    INCLUDEPATH += $$quote(C:\Program Files\marble\include) ../KOMI_MAIN_LIB
    CONFIG(Debug, Debug|Release) {
        LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marbleVS\src\lib\marble\Debug\marblewidget-qt5d.lib) $$quote(../debug/KOMI_MAIN_LIB.lib)
    } else {
        LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marbleVS\src\lib\marble\Release\marblewidget-qt5.lib) $$quote(../release/KOMI_MAIN_LIB.lib)
    }
} else {
    DESTDIR    = ../
    DEPENDPATH += ../KOMI_MAIN_LIB
    INCLUDEPATH += ../KOMI_MAIN_LIB
    LIBS += -L/usr/local/lib \
        -lmarblewidget-qt5 \
        -L../ -lKOMI_MAIN_LIB
}

QMAKE_CXXFLAGS += -std=c++0x


SOURCES += main.cpp\
        mainwindow.cpp \
    mapwidget.cpp \
    komipluginmanager.cpp \
    appinterface.cpp \
    progressbardialog.cpp

HEADERS  += mainwindow.h \
    mapwidget.h \
    komiwojazerplugininterface.h \
    komipluginmanager.h \
    appinterface.h \
    progressbardialog.h

FORMS    += mainwindow.ui \
    progressbardialog.ui

QMAKE_CXXFLAGS += -std=c++0x

RESOURCES += \
    images.qrc
