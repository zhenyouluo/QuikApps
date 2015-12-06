QT       += network sql script xml

QT       -= gui

TARGET = HomeIndexPlugin
TEMPLATE = lib

DEFINES += HomeIndexPLUGIN_LIBRARY

SOURCES += HomeIndexplugin.cpp

HEADERS += HomeIndexplugin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

