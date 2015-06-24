TEMPLATE        = lib
CONFIG         += plugins
QT             += widgets
INCLUDEPATH    += ../komiwojazer $$quote(C:\Program Files (x86)\marble\include) ../KOMI_MAIN_LIB
HEADERS         = komiplugin.h
SOURCES         = komiplugin.cpp
TARGET          = $$qtLibraryTarget(komiPluginExample)
DESTDIR         = ../plugins

win32 {
    CONFIG(Debug, Debug|Release) {
        LIBS += $$quote(C:\Program Files (x86)\marble\libmarblewidget-qt5d.dll) $$quote(../debug/KOMI_MAIN_LIB.dll)
        #LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marble\build\src\lib\marble\libmarblewidget-qt5.dll.a) $$quote(../debug/libKOMI_MAIN_LIB.a)
    } else {
        LIBS += $$quote(C:\Program Files (x86)\marble\libmarblewidget-qt5.dll) $$quote(../release/KOMI_MAIN_LIB.dll)
        #LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marble\buildd\src\lib\marble\libmarblewidget-qt5d.dll.a) $$quote(../release/libKOMI_MAIN_LIB.a)
    }
}
else {
    LIBS += -L/usr/local/lib \
        -lmarblewidget-qt5
}
EXAMPLE_FILES = komiplugin.json
QMAKE_CXXFLAGS += -std=c++0x
