#-------------------------------------------------
#
# Project created by QtCreator 2013-04-05T19:35:15
#
# Compatible desde Qt5.3 en adelante
#-------------------------------------------------

QT       += core gui widgets svg charts network serialport
CONFIG   += qwt analogwidgets colorwidgets embeddeduma qmqtt

TARGET = LoadMonitor
TEMPLATE = app


SOURCES += main.cpp\
        guipanel.cpp \
    crc.c \
    serial2USBprotocol.c

HEADERS  += guipanel.h \
    crc.h \
    serial2USBprotocol.h \
    usb_messages_table.h

FORMS    += guipanel.ui

RESOURCES += \
    imagenes.qrc

RC_ICONS = Designer.ico
