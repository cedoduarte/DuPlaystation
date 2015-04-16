#-------------------------------------------------
#
# Project created by QtCreator 2015-04-09T18:19:03
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DuPlaystation
TEMPLATE = app


#DEFINES += DU_DEBUG

SOURCES += main.cpp\
        MainWindow.cpp \
    DuDatabase.cpp \
    DuPlayButton.cpp

HEADERS  += MainWindow.h \
    DuDatabase.h \
    DuApplication.h \
    DuPlayButton.h \
    DuDefines.h

FORMS    += MainWindow.ui

QMAKE_CXXFLAGS += -std=gnu++14

RESOURCES += \
    res.qrc
