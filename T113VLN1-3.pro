QT += core sql gui widgets

CONFIG += c++11

TARGET = T113VLN1-3
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
    $$PWD/utils.cpp \
    $$PWD/personDialog.cpp \
    $$PWD/gui.cpp \
    $$PWD/computerDialog.cpp \
    mainwindow.cpp \
    prelationc.cpp \
    crelationp.cpp

HEADERS += \
    $$PWD/domain.h \
    $$PWD/data.h \
    $$PWD/utils.h \
    $$PWD/personDialog.h \
    $$PWD/gui.h \
    $$PWD/computerDialog.h \
    mainwindow.h \
    prelationc.h \
    crelationp.h

FORMS += \
    $$PWD/personDialog.ui \
    $$PWD/gui.ui \
    $$PWD/computerDialog.ui \
    mainwindow.ui \
    prelationc.ui \
    crelationp.ui

RESOURCES += \
    resources.qrc
