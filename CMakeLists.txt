cmake_minimum_required(VERSION 3.0)
project(ApkDeeplinkExtractor)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)

set(SOURCE_FILES main.cpp MainWindow.cpp MainWindow.h classes/helpers/FileHelper.cpp classes/helpers/FileHelper.h classes/parser/ManifestParser.cpp classes/parser/ManifestParser.h ui_mainwindow.h)
add_executable(ApkDeeplinkExtractor ${SOURCE_FILES})

qt5_use_modules(ApkDeeplinkExtractor Core Gui Widgets Xml)