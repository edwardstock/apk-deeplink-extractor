cmake_minimum_required(VERSION 3.0)
project(ApkDeeplinkExtractor)

set(CMAKE_PREFIX_PATH "/home/edwardstock/Qt/")

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(BUILD_TYPE "cli")
set(VERSION "1.1.0")

add_definitions(-DBUILD_TYPE="${BUILD_TYPE}")
add_definitions(-DADE_VERSION="${VERSION}")

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)

# cli sources
set(SOURCE_FILES_GUI main_gui.cpp
        app/gui/MainWindow.cpp
        app/gui/MainWindow.h
        ui_mainwindow.h
        classes/helpers/FileHelper.cpp
        classes/helpers/FileHelper.h
        classes/parser/ManifestParser.cpp
        classes/parser/ManifestParser.h
        classes/parser/ApkTool.cpp
        classes/parser/ApkTool.h
        definitions.h
        version.h
        )

# gui sources
set(SOURCE_FILES_CLI
        main_cli.cpp
        classes/helpers/FileHelper.cpp
        classes/helpers/FileHelper.h
        classes/parser/ManifestParser.cpp
        classes/parser/ManifestParser.h
        app/cli/CliParser.cpp
        app/cli/CliParser.h
        classes/parser/ApkTool.cpp
        classes/parser/ApkTool.h
        definitions.h
        version.h
        )

if (APPLE)
    set(EXECUTABLE_OUTPUT_PATH "../build/osx/${BUILD_TYPE}")
elseif (WIN32)
    if (BUILD_TYPE STREQUAL "cli")
        message(FATAL_ERROR "Cannot compile cli tool for Windows")
    endif ()
    set(EXECUTABLE_OUTPUT_PATH "../build/win64/${BUILD_TYPE}")
elseif (UNIX)
    set(EXECUTABLE_OUTPUT_PATH "../build/unix/${BUILD_TYPE}")
endif ()


if (BUILD_TYPE STREQUAL "cli")
    add_definitions(-DADE_CLI)
    add_executable(apk-deeplink-extractor ${SOURCE_FILES_CLI})
    qt5_use_modules(apk-deeplink-extractor Core)

    install(TARGETS apk-deeplink-extractor DESTINATION bin)
    install(FILES apktool apktool.jar DESTINATION bin)
    add_custom_target(install_${PROJECT_NAME}
            $(MAKE) install
            COMMENT "Installing ${PROJECT_NAME}")
else ()
    add_executable(ApkDeeplinkExtractor ${SOURCE_FILES_GUI})
    qt5_use_modules(ApkDeeplinkExtractor Core Gui Widgets)
endif ()
