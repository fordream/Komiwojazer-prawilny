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
    INCLUDEPATH += $$quote(C:\Program Files (x86)\marble\include) ../KOMI_MAIN_LIB
    CONFIG(Debug, Debug|Release) {
        LIBS += $$quote(C:\Program Files (x86)\marble\libmarblewidget-qt5d.dll) $$quote(../debug/KOMI_MAIN_LIB.dll)
        #LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marble\build\src\lib\marble\libmarblewidget-qt5.dll.a) $$quote(../debug/libKOMI_MAIN_LIB.a)
    } else {
        LIBS += $$quote(C:\Program Files (x86)\marble\libmarblewidget-qt5.dll) $$quote(../release/KOMI_MAIN_LIB.dll)
        #LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marble\buildd\src\lib\marble\libmarblewidget-qt5d.dll.a) $$quote(../release/libKOMI_MAIN_LIB.a)
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
    progressbardialog.cpp \
    listwithbuttons.cpp \
    browser.cpp

HEADERS  += mainwindow.h \
    mapwidget.h \
    komiwojazerplugininterface.h \
    komipluginmanager.h \
    appinterface.h \
    progressbardialog.h \
    listwithbuttons.h \
    browser.h

FORMS    += mainwindow.ui \
    progressbardialog.ui \
    listwithbuttons.ui \
    browser.ui

QMAKE_CXXFLAGS += -std=c++0x

RESOURCES += \
    images.qrc
