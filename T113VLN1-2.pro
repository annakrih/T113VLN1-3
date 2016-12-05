QT += core sql
QT -= gui

CONFIG += c++11

TARGET = T113VLN1-2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    person.cpp \
    ui.cpp \
    domain.cpp \
    data.cpp \
    config.cpp \
    computer.cpp

HEADERS += \
    person.h \
    ui.h \
    domain.h \
    data.h \
    config.h \
    computer.h
