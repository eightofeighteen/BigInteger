#-------------------------------------------------
#
# Project created by QtCreator 2016-04-28T06:10:57
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = BigInteger
CONFIG   += console
CONFIG   -= app_bundle
#CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    biginteger.cpp \
    sharedmemorycontroller.cpp \
    sharedmemory2.cpp

LIBS += -lcryptopp

HEADERS += \
    biginteger.h \
    sharedmemorycontroller.h \
    sharedmemory2.h
