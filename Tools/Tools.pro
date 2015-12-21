#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T23:24:36
#
#-------------------------------------------------

QT       -= gui

TARGET = Tools
TEMPLATE = lib
CONFIG += staticlib

SOURCES += tools.cpp \
    cprotocol.cpp \
    ctransport.cpp \
    csocket.cpp \
    cbinaryprotocol.cpp \
    cdefaultprotocol.cpp \
    cservertransport.cpp \
    cserversocket.cpp

HEADERS += tools.h \
    cprotocol.h \
    ctransport.h \
    csocket.h \
    cbinaryprotocol.h \
    cdefaultprotocol.h \
    cservertransport.h \
    cserversocket.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
