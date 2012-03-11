#-------------------------------------------------
#
# Project created by QtCreator 2010-06-08T19:00:38
#
#-------------------------------------------------

TEMPLATE    = app

DESTDIR     = bin
TARGET      = MouseSense

CONFIG     += qxt
QXT        += core gui

OBJECTS_DIR = build/os
UI_DIR      = build/uis
MOC_DIR     = build/mocs
RCC_DIR     = build/rccs

SOURCES    += src/main.cpp\
              src/mainwindow.cpp \
              src/devicedialog.cpp

HEADERS    += src/mainwindow.h \
              src/devicedialog.h

FORMS      += src/forms/mainwindow.ui \
              src/forms/devicedialog.ui

RESOURCES  += src/qrc/resources.qrc


include(qtsingleapplication-2.6_1-opensource/src/qtsingleapplication.pri)

QMAKE_CXXFLAGS_DEBUG += -g3 \
    -O0
QMAKE_CXXFLAGS_RELEASE += -g0 \
    -O3
