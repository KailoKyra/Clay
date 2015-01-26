#-------------------------------------------------
#
# Project created by QtCreator 2014-07-08T23:39:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../claymulator
TEMPLATE = app


SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp

HEADERS  += \
    includes/MainWindow.h

FORMS    += \
    src/MainWindow.ui

INCLUDEPATH +=          \
    includes            \
    ../core/includes

RESOURCES += \
    data/res.qrc

LIBS += -L"$$_PRO_FILE_PWD_/../core" -lclayCore -L"$$_PRO_FILE_PWD_/../libz80" -lz80
