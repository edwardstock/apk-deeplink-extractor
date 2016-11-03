/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2016 					                               *
 *   https://github.com/edwardstock										   *
 *   Author: Eduard Maximovich <edward.vstock@gmail.com>				   *
 *                                                                         *
 ***************************************************************************/

#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("APK Deeplink Extractor Tool");

    this->apkPath = QString();

    connect(ui->apkSelect, SIGNAL(clicked()), this, SLOT(openFileDialog()));
    connect(ui->extract, SIGNAL(clicked()), this, SLOT(extractFile()));
}

void MainWindow::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Select APK file"),
        QDir::homePath(),
        tr("Android APK file (*.apk)")
    );

    this->apkPath = filePath;
    this->tmpDir = QDir::tempPath();
    this->tmpDir
        .append("/")
        .append(
            QCryptographicHash::hash((filePath.toLocal8Bit()), QCryptographicHash::Md5).toHex()
        );

    QDir t(this->tmpDir);
    if (!t.exists()) {
        if (!t.mkpath(this->tmpDir)) {
            this->showError("Cannot create tmp dir");
            return;
        }

        qDebug() << "Trying to create tmp dir: " << this->tmpDir;
    }

    this->ui->selectedFile->setText(filePath);
}

void MainWindow::extractFile()
{
    if (!apkSelected()) {
        this->showError("Please, choose file first");
        return;
    }

    if (manifestExtracted()) {
        extractFinished(0, QProcess::ExitStatus::NormalExit);
        return;
    }

    QProcess *p = new QProcess(this);
    if (p == NULL) {
        this->showError("Cannot open external process");
        return;
    }

    QStringList arguments;
    QString execArg = QDir::currentPath().append("/").append(EXECUTABLE);
    QString cmd(SYS_EX);

    if (!FileHelper::exists(cmd) || !FileHelper::isExecutable(cmd) || !FileHelper::exists(execArg)
        || !FileHelper::isExecutable(execArg)) {
        this->showError(QString("Cannot find or execute command ").append(cmd));
        return;
    }

    if (QString(SYS_EX_ARG) != "") {
        arguments << SYS_EX_ARG;
    }

#ifdef _WIN32
    arguments << execArg
                 .append(" d ").append(this->apkPath)
                 .append(" -f")
                 .append(" --output ").append(this->tmpDir);
#else
    arguments << execArg;
    arguments << "d" << this->apkPath;
    arguments << "-f";
    arguments << "--output" << this->tmpDir;
#endif

    ui->processResult->append(arguments.join(" "));

    p->setProcessChannelMode(QProcess::MergedChannels);
    p->start(cmd, arguments);
    p->waitForStarted();

    connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(writeOutput()));
    connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(extractFinished(int, QProcess::ExitStatus)));
}

void MainWindow::writeOutput()
{
    QProcess *process = dynamic_cast<QProcess *>( sender());
    ui->processResult->append(process->readAllStandardOutput());
    ui->processResult->append(process->readAllStandardError());
}

void MainWindow::extractFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Finished: " << exitCode;
    qDebug() << "Finished status: " << exitStatus;
    if (exitCode == 0) {
        ui->processResult->append("Extracting done.");
        QProcess *process = dynamic_cast<QProcess *>( sender());
        delete process;
    }

    ManifestParser *parser = new ManifestParser(getManifestPath());

    if (!parser->parse()) {
        this->ui->outDeeplinks->append("No one deeplink was found");
    } else {
        QVector<ManifestParser::Link> links = parser->getDeeplinks();
            foreach (ManifestParser::Link link, links) {
                this->ui->outDeeplinks->append(QString(link.scheme).append("://").append(link.route));
            }
    }

    delete parser;
}

int MainWindow::showError(const QString text)
{
    QMessageBox m(this);
    m.setWindowTitle("Error");
    m.setText(text);
    m.setStandardButtons(QMessageBox::Ok);
    return m.exec();
}

bool MainWindow::apkSelected()
{
    return !(this->apkPath.isNull() || this->apkPath == "");
}

bool MainWindow::manifestExtracted()
{
    return QFile(getManifestPath()).exists();
}

QString MainWindow::getManifestPath()
{
    return QString(this->tmpDir).append("/AndroidManifest.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
}
