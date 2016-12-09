QT += core sql gui widgets

CONFIG += c++11

TARGET = T113VLN1-2
CONFIG += console
CONFIG -= app_bundle

release:DESTDIR = $${PWD}/release
release:OBJECTS_DIR = $${PWD}/release/.obj
release:MOC_DIR = $${PWD}/release/.moc
release:RCC_DIR = $${PWD}/release/.rcc
release:UI_DIR = $${PWD}/release/.ui

debug:DESTDIR = $${PWD}/debug
debug:OBJECTS_DIR = $${PWD}/debug/.obj
debug:MOC_DIR = $${PWD}/debug/.moc
debug:RCC_DIR = $${PWD}/debug/.rcc
debug:UI_DIR = $${PWD}/debug/.ui

TEMPLATE = app

SOURCES += $$PWD/main.cpp \
    $$PWD/domain.cpp \
    $$PWD/data.cpp \
    $$PWD/config.cpp \
    $$PWD/utils.cpp \
    $$PWD/personDialog.cpp \
    $$PWD/gui.cpp \
    $$PWD/searchPersonDialog.cpp \
    $$PWD/searchComputerDialog.cpp \
    $$PWD/computerDialog.cpp

HEADERS += \
    $$PWD/domain.h \
    $$PWD/data.h \
    $$PWD/config.h \
    $$PWD/utils.h \
    $$PWD/personDialog.h \
    $$PWD/gui.h \
    $$PWD/searchComputerDialog.h \
    $$PWD/searchPersonDialog.h \
    $$PWD/computerDialog.h

FORMS += \
    $$PWD/personDialog.ui \
    $$PWD/gui.ui \
    $$PWD/searchComputerDialog.ui \
    $$PWD/searchPersonDialog.ui \
    $$PWD/computerDialog.ui
