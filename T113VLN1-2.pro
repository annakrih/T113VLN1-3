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
    $$PWD/person.cpp \
    $$PWD/ui.cpp \
    $$PWD/domain.cpp \
    $$PWD/data.cpp \
    $$PWD/config.cpp \
    $$PWD/computer.cpp \
    utils.cpp \
    personDialog.cpp \
    gui.cpp \
<<<<<<< HEAD
    searchDialog.cpp \
    searchComputerDialog.cpp
=======
    searchPersonDialog.cpp
>>>>>>> origin/master

HEADERS += \
    $$PWD/person.h \
    $$PWD/ui.h \
    $$PWD/domain.h \
    $$PWD/data.h \
    $$PWD/config.h \
    $$PWD/computer.h \
    utils.h \
    personDialog.h \
    gui.h \
<<<<<<< HEAD
    searchDialog.h \
    searchDomputerDialog.h
=======
    searchPersonDialog.h
>>>>>>> origin/master

FORMS += \
    personDialog.ui \
    gui.ui \
<<<<<<< HEAD
    searchDialog.ui \
    searchComputerDialog.ui
=======
    searchPersonDialog.ui
>>>>>>> origin/master
