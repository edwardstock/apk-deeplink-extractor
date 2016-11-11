/**
 * ApkDeeplinkExtractor
 * MainWindow.h
 *
 * @author Eduard Maximovich <edward.vstock@gmail.com>
 * @link https://github.com/edwardstock
 * @copyright 2016 GNU General Public License v3
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QTextEdit>
#include <QProcess>
#include <QPushButton>
#include <QString>
#include <QDesktopServices>
#include <QVector>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QMetaEnum>
#include <QSettings>
#include <QVariant>
#include "classes/helpers/FileHelper.h"
#include "classes/parser/ManifestParser.h"
#include "classes/parser/ApkTool.h"
#include "definitions.h"
#include "version.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void setLastOpenPath(QString path);

public slots:

    void openFileDialog();

    void writeOutput(QString s, bool error);

    void processComplete(QVector<ManifestParser::Link> &deeplinks);

    void processStatus(ApkTool::Status status);

    void extractFile();

private:
    Ui::MainWindow *ui;

    QString lastOpenPath;

    /**
     * Path to selected apk file
     */
    QString apkPath;

    /**
     * Temporary dir where will stored apktool data
     */
    QString tmpDir;

    /**
     * App settings
     */
    QSettings *settings;

    int showError(const QString text);
};

#endif // MAINWINDOW_H
