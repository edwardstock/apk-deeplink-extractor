#-------------------------------------------------
#
# Project created by QtCreator 2016-11-02T19:09:34
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ApkDeeplinkExtractor

TEMPLATE = app

ICON = res/icon.icns

SOURCES += main.cpp\
        mainwindow.cpp \
    filehelper.cpp \
    manifestparser.cpp

HEADERS  += mainwindow.h \
    filehelper.h \
    manifestparser.h

FORMS    += mainwindow.ui

DISTFILES += apktool \
    apktool.jar \
    install_apktool.sh \
    apktool.bat \
    res/icon.png \
    res/icon.ico \
    res/icon.icns \
    license \
    .gitignore

APKTOOL_EX.files = apktool apktool.bat apktool.jar install_apktool.sh
APKTOOL_EX.path = Contents/Resources

QMAKE_BUNDLE_DATA += APKTOOL_EX

ext_tool.path = $${OUT_PWD}
ext_tool.files += $${PWD}/apktool
ext_tool.files += $${PWD}/apktool.jar
ext_tool.files += $${PWD}/install_apktool.sh

INSTALLS += ext_tool

VERSION = "1.0.0"

DEFINES += "ADE_VERSION=1.0.0"

QMAKE_TARGET_COMPANY = RussianVentures

