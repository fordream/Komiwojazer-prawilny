TEMPLATE        = lib
CONFIG         += plugins
QT             += widgets
INCLUDEPATH    += ../komiwojazer $$quote(E:\Program Files\Marble\include)
HEADERS         = komiplugin.h
SOURCES         = komiplugin.cpp
TARGET          = $$qtLibraryTarget(komiPluginExample)
DESTDIR         = ../plugins
<<<<<<< HEAD
LIBS += -L/usr/local/lib \
        -lmarblewidget-qt5
=======

win32 {
    CONFIG(Debug, Debug|Release) {
        LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marbleVS\src\lib\marble\Debug\marblewidget-qt5d.lib)
    } else {
        LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marbleVS\src\lib\marble\Release\marblewidget-qt5.lib)
    }
}
>>>>>>> 4e7c9d679e4e07dc50633b9fa9acd0337ad1cf97
EXAMPLE_FILES = komiplugin.json
