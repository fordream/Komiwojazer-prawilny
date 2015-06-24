#-------------------------------------------------
#
# Project created by QtCreator 2015-06-21T22:39:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KOMI_MAIN_LIB
TEMPLATE = lib

DEFINES += KOMI_MAIN_LIB_LIBRARY

SOURCES += komi_main_lib.cpp \
        geolistitem.cpp \
        coordinates.cpp \
        place.cpp

HEADERS += komi_main_lib.h\
        komi_main_lib_global.h \
        geolistitem.h \
        coordinates.h \
        place.h

win32 {
    CONFIG(debug, release|debug):DESTDIR = ../debug/
    CONFIG(release, release|debug):DESTDIR = ../release/
    INCLUDEPATH += $$quote(C:\Program Files (x86)\marble\include)
    CONFIG(Debug, Debug|Release) {
        LIBS += $$quote(C:\Program Files (x86)\marble\libmarblewidget-qt5d.dll)
        #LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marble\build\src\lib\marble\libmarblewidget-qt5.dll.a)
    } else {
        LIBS += $$quote(C:\Program Files (x86)\marble\libmarblewidget-qt5.dll)
        #LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marble\buildd\src\lib\marble\libmarblewidget-qt5d.dll.a)
    }
} unix {
    DESTDIR    = ../
    LIBS += -L/usr/local/lib \
    -lmarblewidget-qt5
    INSTALLS += target
}

QMAKE_CXXFLAGS += -std=c++0x
