#-------------------------------------------------
#
# Project created by QtCreator 2014-03-22T14:54:55
#
#-------------------------------------------------
#Windows
#LIBS += -L"../Liberty2/libs" -lpython27
#LIBS += -L"/usr/lib/x86_64-linux-gnu/" /usr/lib/x86_64-linux-gnu/libpython2.7.a -lz -lQtWebKit
#LIBS += -L"/usr/lib/x86_64-linux-gnu/" -lpython2.7 -lz
#Windows
#INCLUDEPATH += include
#INCLUDEPATH += /usr/include/python2.7/

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT       += webkitwidgets widgets
!greaterThan(QT_MAJOR_VERSION, 4): QT       += webkit
#for qt 5 add webkitwidgets
QMAKE_CXXFLAGS +=  -Wno-unused-parameter
greaterThan(QT_MAJOR_VERSION, 4): QMAKE_CXXFLAGS += -DUSE_QT5

win32{
    QMAKE_CXXFLAGS += -DWINDOWS
#    LIBS += -L"../Liberty3/libs" -lpython27
    INCLUDEPATH += include
}

unix{
#    LIBS += -L"/usr/lib/x86_64-linux-gnu/" -lpython2.7
    INCLUDEPATH += /usr/include/python2.7/
}

TARGET = QuikApps
#TEMPLATE = app


SOURCES += main.cpp\
    downloader.cpp \
    localreply.cpp \
    localview.cpp \
    mimetypes.cpp \
    networkaccessmanager.cpp \
    mainwindow.cpp \
    localapp.cpp

HEADERS  += \
    apptypes.h \
    downloader.h \
    localreply.h \
    localview.h \
    mimetypes.h \
    networkaccessmanager.h \
    qfileerror.h \
    mainwindow.h \
    UiMainWindow.h \
    global.h \
    localapp.h

FORMS +=

RESOURCES += \
    icons.qrc

OTHER_FILES += \
    app32.png \
    app64.png \
    app128.png \
    back.png \
    forward.png \
    go.png \
    refresh.png \
    stop.png
