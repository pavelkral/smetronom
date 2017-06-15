
QT += core gui network xml multimedia

#android: QT += androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TEMPLATE = app
RESOURCES += smetronom.qrc
TARGET = smetronom
DESTDIR = $$OUT_PWD/bin

SOURCES += main.cpp \
    widget.cpp \ 
#  androidfiledialog.cpp \
    dialog.cpp

HEADERS += widget.h \
#   androidfiledialog.h \
    dialog.h

FORMS += widget.ui \
    dialog.ui

RC_FILE = smetronom.rc


DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
