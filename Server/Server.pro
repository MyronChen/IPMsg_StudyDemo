QT += core
QT -= gui

TARGET = Server
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    accunthandler.cpp \
    ../AccountService/accountservice.cpp \
    mysqltool.cpp \
    userlist.cpp \
    session.cpp \
    ../AccountService/accountservicetype.cpp


unix:!macx: LIBS += -L$$PWD/../obj/ -lTools
unix|win32: LIBS += -lmysqlclient

INCLUDEPATH += $$PWD/../Tools
DEPENDPATH += $$PWD/../Tools

unix:!macx: PRE_TARGETDEPS += $$PWD/../obj/libTools.a

HEADERS += \
    accunthandler.h \
    ../AccountService/accountservice.h \
    serverpri.h \
    userlist.h \
    binaryprotocol.h \
    session.h \
    ../AccountService/accountservicetype.h
