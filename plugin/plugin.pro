TEMPLATE        = lib
CONFIG         += plugins
QT             += widgets
INCLUDEPATH    += ../komiwojazer
HEADERS         = komiplugin.h
SOURCES         = komiplugin.cpp
TARGET          = $$qtLibraryTarget(komiplugin)
DESTDIR         = ../plugins
LIBS += -L/usr/local/lib \
        -lmarblewidget-qt5
EXAMPLE_FILES = komiplugin.json
