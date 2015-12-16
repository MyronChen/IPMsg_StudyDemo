#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T21:26:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IPMsg
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    registerdialog.cpp \
    ipmessage.cpp \
    util.cpp \
    serverstub.cpp \
    ../AccountService/accountservice.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    registerdialog.h \
    ipmessage.h \
    util.h \
    serverstub.h \
    ../AccountService/accountservice.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    registerdialog.ui

INCLUDEPATH += ../


unix:!macx: LIBS += -L$$PWD/../build-Tools-Desktop_Qt_5_5_1_GCC_64bit-Debug/ -lTools

INCLUDEPATH += $$PWD/../Tools
DEPENDPATH += $$PWD/../Tools

unix:!macx: PRE_TARGETDEPS += $$PWD/../build-Tools-Desktop_Qt_5_5_1_GCC_64bit-Debug/libTools.a
