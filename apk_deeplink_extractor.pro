#-------------------------------------------------
#
# Project created by QtCreator 2016-11-02T19:09:34
#
#-------------------------------------------------

QT       += core

lessThan(QT_MAJOR_VERSION, 5): error("requires Qt 5")

TARGET = ApkDeeplinkExtractor

TEMPLATE = app

ICON = res/icon.icns
win32:RC_ICONS += res/winicon.ico
RC_FILE += resources.rc

QMAKE_TARGET_COMPANY = "Eduard Maximovich"
QMAKE_TARGET_PRODUCT = "Apk Deeplink Extractor"
QMAKE_TARGET_DESCRIPTION = "Apk Deeplink extractor"
QMAKE_TARGET_COPYRIGHT = "Copyright © 2016 Eduard Maximovich"

SOURCES += classes/helpers/FileHelper.cpp \
    classes/parser/ManifestParser.cpp \
    classes/parser/ApkTool.cpp

HEADERS  += classes/helpers/FileHelper.h \
    classes/parser/ManifestParser.h \
    version.h \
    definitions.h \
    classes/parser/ApkTool.h \
    ui_mainwindow.h

DISTFILES += apktool \
    apktool.jar \
    install_apktool.sh \
    apktool.bat \
    res/icon.png \
    res/icon.ico \
    res/icon.icns \
    res/winicon.ico \
    .gitignore \
    resources.rc \
    config.ini

APKTOOL_EX.files = apktool apktool.bat apktool.jar install_apktool.sh
APKTOOL_EX.path = Contents/Resources

QMAKE_BUNDLE_DATA += APKTOOL_EX

ext_tool.path = $${OUT_PWD}
ext_tool.files += $${PWD}/apktool
ext_tool.files += $${PWD}/apktool.jar
ext_tool.files += $${PWD}/install_apktool.sh
INSTALLS += ext_tool

VERSION = "1.1.0"

DEFINES += ADE_VERSION=\\\"$$VERSION\\\"

console {
    DEFINES += BUILD_TYPE="cli"
    DEFINES += ADE_CLI
    SOURCES += main_cli.cpp app/cli/CliParser.cpp
    HEADERS += app/cli/CliParser.h
    CONFIG  -= app_bundle
} else {
    SOURCES += main_gui.cpp app/gui/MainWindow.cpp
    HEADERS += app/gui/MainWindow.h ui_mainwindow.h
    DEFINES += BUILD_TYPE="gui"
    QT      += gui widgets
    FORMS   += mainwindow.ui
}

win32-msvc* {
    EXTRA_BINFILES += $${PWD}/apktool.bat $${PWD}/apktool.jar $${PWD}/install_apktool.sh
    EXTRA_BINFILES_WIN = $${EXTRA_BINFILES}
    EXTRA_BINFILES_WIN ~= s,/,\\,g
    DESTDIR_WIN = $${DESTDIR}

    DESTDIR_WIN ~= s,/,\\,g
    for(FILE, EXTRA_BINFILES_WIN){
        message("Copying file $${FILE}")
        QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DESTDIR_WIN}$$escape_expand(\n\t))
    }
}

!win32-msvc* {
    QMAKE_CXXFLAGS += -std=c++11
}
