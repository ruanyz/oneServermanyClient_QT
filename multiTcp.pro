#-------------------------------------------------
#
# Project created by QtCreator 2018-09-03T22:26:47
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multiTcp
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    server.cpp \
    socket.cpp \
    socketthread.cpp \
#    client.cpp \
    form.cpp

HEADERS  += widget.h \
    server.h \
    socket.h \
    socketthread.h \
#    client.h \
    form.h

FORMS    += widget.ui \
#    client.ui \
    form.ui
