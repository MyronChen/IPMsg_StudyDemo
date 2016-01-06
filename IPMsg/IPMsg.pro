QT       += core gui
CONFIG += c++11

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
    ../AccountService/accountservice.cpp \
    ../AccountService/accountservicetype.cpp \
    chatdialog.cpp \
    chatsession.cpp \
    chatmanager.cpp \
    udpsocket.cpp \
    chatmessage.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    registerdialog.h \
    ipmessage.h \
    util.h \
    serverstub.h \
    ../AccountService/accountservice.h \
    binaryprotocol.h \
    ../AccountService/accountservicetype.h \
    chatdialog.h \
    chatsession.h \
    chatmanager.h \
    udpsocket.h \
    chatmessage.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    registerdialog.ui \
    chatdialog.ui

INCLUDEPATH += ../


unix:!macx: LIBS += -L$$PWD/../obj/ -lTools

INCLUDEPATH += $$PWD/../Tools
DEPENDPATH += $$PWD/../Tools

unix:!macx: PRE_TARGETDEPS += $$PWD/../obj/libTools.a
