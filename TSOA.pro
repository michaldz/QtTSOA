#-------------------------------------------------
#
# Project created by QtCreator 2012-06-05T18:27:51
#
#-------------------------------------------------

QT       += core gui

TARGET = TSOA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    test.cpp \
    TS.cpp \
    Sick.cpp \
    Laser.cpp \
    Connector.cpp \
    Algorithm.cpp

HEADERS  += mainwindow.h \
    test.h \
    TS.h \
    Sick.h \
    Laser.h \
    Connector.h \
    Algorithm.h
FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/player-3.0/
LIBS += -L/usr/local/lib -lplayerc++

CFLAGS += playerc++

INCLUDEPATH += /usr/local/qwt-6.0.1/include
LIBS += /usr/local/qwt-6.0.1/lib/libqwt.so

CONFIG += qwt
