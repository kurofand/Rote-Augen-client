#-------------------------------------------------
#
# Project created by QtCreator 2017-06-03T01:55:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = screenClient
TEMPLATE = app


SOURCES += main.cpp\
        screenmain.cpp \
    clientsender.cpp

HEADERS  += screenmain.h \
    clientsender.h

FORMS    += screenmain.ui
