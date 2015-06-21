TEMPLATE        = lib
CONFIG         += plugins
QT             += widgets
INCLUDEPATH    += ../komiwojazer $$quote(E:\Program Files\Marble\include)
HEADERS         = komiplugin.h
SOURCES         = komiplugin.cpp
TARGET          = $$qtLibraryTarget(komiPlugin-2-opt)
DESTDIR         = ../plugins

win32 {
    CONFIG(Debug, Debug|Release) {
        LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marbleVS\src\lib\marble\Debug\marblewidget-qt5d.lib)
    } else {
        LIBS += $$quote(E:\Michal\Projects\C++\MarbleKomi\marbleVS\src\lib\marble\Release\marblewidget-qt5.lib)
    }
}
EXAMPLE_FILES = komiplugin.json
