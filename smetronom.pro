
QT += core gui network xml multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TEMPLATE = app
RESOURCES += smetronom.qrc
TARGET = smetronom
DESTDIR = $$OUT_PWD/bin

SOURCES += main.cpp \
    widget.cpp 

HEADERS += widget.h \

FORMS += widget.ui

RC_FILE = smetronom.rc
