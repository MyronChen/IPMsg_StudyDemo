QT += core
QT -= gui

TARGET = Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    accunthandler.cpp \
    ../AccountService/accountservice.cpp


unix:!macx: LIBS += -L$$PWD/../build-Tools-Desktop_Qt_5_5_1_GCC_64bit-Debug/ -lTools

INCLUDEPATH += $$PWD/../Tools
DEPENDPATH += $$PWD/../Tools

unix:!macx: PRE_TARGETDEPS += $$PWD/../build-Tools-Desktop_Qt_5_5_1_GCC_64bit-Debug/libTools.a

HEADERS += \
    accunthandler.h \
    ../AccountService/accountservice.h
