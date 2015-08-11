#-------------------------------------------------
#
# Project created by QtCreator 2015-07-28T23:43:15
#
#-------------------------------------------------

QT       += network sql script xml

QT       -= gui

TARGET = LibertyPlugin
TEMPLATE = lib

DEFINES += LIBERTYPLUGIN_LIBRARY

SOURCES += libertyplugin.cpp

HEADERS += libertyplugin.h\
        libertyplugin_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
