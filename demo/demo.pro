#-------------------------------------------------
#
# Project created by QtCreator 2014-05-02T13:27:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo
TEMPLATE = app

BUILD_DIR = ../build/demo
DESTDIR = ../bin
OBJECTS_DIR = $$BUILD_DIR
MOC_DIR = $$BUILD_DIR
RCC_DIR = $$BUILD_DIR
UI_DIR = $$BUILD_DIR
PRECOMPILED_DIR = $$BUILD_DIR

INCLUDEPATH += ../src

unix {
    LIBS += -L../lib -lqnavigation
}

SOURCES += main.cpp\
    scene.cpp \
    controller.cpp

HEADERS  += \
    scene.h \
    controller.h

FORMS += \
    scene.ui
