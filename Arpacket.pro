#-------------------------------------------------
#
# Project created by QtCreator 2016-10-22T21:40:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Arpacket
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    MACTableModel.cpp \
    arp.cpp

HEADERS  += mainwidget.h \
    MACTableModel.h \
    arp.h \
    global.h


INCLUDEPATH += $$PWD/npcap-sdk/Include

LIBS += -L$$PWD/npcap-sdk/Lib -lPacket
LIBS += -L$$PWD/npcap-sdk/Lib -lwpcap
