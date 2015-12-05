#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T10:00:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = source
TEMPLATE = app

INCLUDEPATH += $$PWD/../include

SOURCES += main.cpp\
    application.cpp \
    commandline.cpp

HEADERS  += \
    application.h \
    commandline.h

TRANSLATIONS = $$PWD/../lang/source/source_en.ts

FORMS    +=

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../plugins/singleapplication/release/ -lsingleapplication
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../plugins/singleapplication/debug/ -lsingleapplication
else:unix: LIBS += -L$$OUT_PWD/../plugins/singleapplication/ -lsingleapplication

INCLUDEPATH += $$PWD/../plugins/singleapplication
DEPENDPATH += $$PWD/../plugins/singleapplication

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../plugins/singleapplication/release/libsingleapplication.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../plugins/singleapplication/debug/libsingleapplication.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../plugins/singleapplication/release/singleapplication.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../plugins/singleapplication/debug/singleapplication.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../plugins/singleapplication/libsingleapplication.a
