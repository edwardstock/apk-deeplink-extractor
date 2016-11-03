/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2016 					                               *
 *   https://github.com/edwardstock										   *
 *   Author: Eduard Maximovich <edward.vstock@gmail.com>				   *
 *                                                                         *
 ***************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QProcess>
#include <QPushButton>
#include <QString>
#include <QDesktopServices>
#include <QVector>
#include "classes/helpers/FileHelper.h"
#include "classes/parser/ManifestParser.h"

#ifdef _WIN32
#define EXECUTABLE "apktool.bat"
#define SYS_EX "cmd.exe"
#define SYS_EX_ARG "/C"
#elif __APPLE__ && __MACH__
#define EXECUTABLE "../Resources/apktool" // package resource dir
#define SYS_EX "/bin/sh"
#define SYS_EX_ARG ""
#else
#define EXECUTABLE "apktool"
#define SYS_EX "/bin/sh"
#define SYS_EX_ARG ""
#endif

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{

Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openFileDialog();
    void extractFile();
    void writeOutput();
    void extractFinished(int, QProcess::ExitStatus);

private:
    Ui::MainWindow *ui;
    QString apkPath;
    QString tmpDir;

    int showError(const QString text);
    void parseManifest();

    bool apkSelected();
    bool manifestExtracted();
    QString getManifestPath();

};

#endif // MAINWINDOW_H
