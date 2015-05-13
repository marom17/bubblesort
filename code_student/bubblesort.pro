#-------------------------------------------------
#
# Project created by QtCreator 2015-04-24T16:51:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = bubblesort
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    sorttester.cpp \
    sortthread.cpp

HEADERS += \
    bubblesort.h \
    isort.h \
    bubblesortthreaded.h \
    sorttester.h \
    moniteurbubble.h \
    moniteurcasepartagee.h \
    sortthread.h
