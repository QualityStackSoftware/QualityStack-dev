#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T22:29:55
#
#-------------------------------------------------

TARGET = singleapplication
TEMPLATE = lib
CONFIG += staticlib

SOURCES += singleapplication.cpp \
    oncerunchecker.cpp

HEADERS += singleapplication.h \
    oncerunchecker.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
