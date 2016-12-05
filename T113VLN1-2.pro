QT += core sql
QT -= gui

CONFIG += c++11

TARGET = T113VLN1-2
CONFIG += console
CONFIG -= app_bundle

Release:DESTDIR = $${PWD}/release
Release:OBJECTS_DIR = $${PWD}/release/.obj
Release:MOC_DIR = $${PWD}/release/.moc
Release:RCC_DIR = $${PWD}/release/.rcc
Release:UI_DIR = $${PWD}/release/.ui

Debug:DESTDIR = $${PWD}/debug
Debug:OBJECTS_DIR = $${PWD}/debug/.obj
Debug:MOC_DIR = $${PWD}/debug/.moc
Debug:RCC_DIR = $${PWD}/debug/.rcc
Debug:UI_DIR = $${PWD}/debug/.ui

TEMPLATE = app

SOURCES += $$PWD/main.cpp \
    $$PWD/person.cpp \
    $$PWD/ui.cpp \
    $$PWD/domain.cpp \
    $$PWD/data.cpp \
    $$PWD/config.cpp \
    $$PWD/computer.cpp

HEADERS += \
    $$PWD/person.h \
    $$PWD/ui.h \
    $$PWD/domain.h \
    $$PWD/data.h \
    $$PWD/config.h \
    $$PWD/computer.h
