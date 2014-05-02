#-------------------------------------------------
#
# Project created by QtCreator 2014-05-02T10:53:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qnavigation
TEMPLATE = lib

#
# Boilerplate
#
BUILD_DIR = ../build/src
DESTDIR = ../lib
OBJECTS_DIR = $$BUILD_DIR
MOC_DIR = $$BUILD_DIR
RCC_DIR = $$BUILD_DIR
UI_DIR = $$BUILD_DIR
PRECOMPILED_DIR = $$BUILD_DIR

#
# Project settings
#
DEFINES += QNAVIGATION_LIBRARY

SOURCES += \
    slidingstackedwidget.cpp \
    navigationwidget.cpp

HEADERS += \
    qnavigation_global.h \
    slidingstackedwidget.h \
    navigationwidget.h

PUBLIC_HEADERS = \
    qnavigation_global.h \
    slidingstackedwidget.h \
    navigationwidget.h

#
# Deploy
#
isEmpty(QNAVIGATION_INSTALL_PREFIX) {  # If the user had set this, honor that
    QNAVIGATION_INSTALL_PREFIX = $$[QT_INSTALL_PREFIX]
    unix {
        QNAVIGATION_INSTALL_PREFIX = /usr/local/qusb
    }
    win32 {
        QNAVIGATION_INSTALL_PREFIX = C:/qusb
    }
}

headers.files = $${PUBLIC_HEADERS}
headers.path = $${QNAVIGATION_INSTALL_PREFIX}/include/qusb
target.path = $${QNAVIGATION_INSTALL_PREFIX}/lib

INSTALLS += headers target
