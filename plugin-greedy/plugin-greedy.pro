TEMPLATE        = lib
CONFIG         += plugins
QT             += widgets
INCLUDEPATH    += ../komiwojazer $$quote(C:\Program Files\marble\include) ../KOMI_MAIN_LIB
HEADERS         = komiplugin.h
SOURCES         = komiplugin.cpp
TARGET          = $$qtLibraryTarget(komiPlugin-greedy)
DESTDIR         = ../plugins

win32 {
    CONFIG(Debug, Debug|Release) {
        LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marbleVS\src\lib\marble\Debug\marblewidget-qt5d.lib)  $$quote(../debug/KOMI_MAIN_LIB.lib)
    } else {
        LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marbleVS\src\lib\marble\Release\marblewidget-qt5.lib) $$quote(../release/KOMI_MAIN_LIB.lib)
    }
}
else {
    LIBS += -L/usr/local/lib \
        -lmarblewidget-qt5
}
EXAMPLE_FILES = komiplugin.json
QMAKE_CXXFLAGS += -std=c++0x
