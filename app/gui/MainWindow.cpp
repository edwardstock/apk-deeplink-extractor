/**
 * ApkDeeplinkExtractor
 * MainWindow.cpp
 *
 * @author Eduard Maximovich <edward.vstock@gmail.com>
 * @link https://github.com/edwardstock
 * @copyright 2016 GNU General Public License v3
 */

#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle(VER_INTERNALNAME_STR);

    this->apkPath = QString();

    connect(ui->apkSelect, SIGNAL(clicked()), this, SLOT(openFileDialog()));
    connect(ui->extract, SIGNAL(clicked()), this, SLOT(extractFile()));

    this->settings = new QSettings(QDir::currentPath() + "/config.ini", QSettings::IniFormat);
    this->settings->beginGroup("MainWindow");
    this->lastOpenPath = this->settings->value("lastOpenPath").toString();
    this->settings->endGroup();
}

MainWindow::~MainWindow() {
    this->settings->beginGroup("MainWindow");
    this->settings->setValue("lastOpenPath", QVariant(this->lastOpenPath));
    this->settings->endGroup();
    this->settings->sync();

    delete ui;
    delete settings;

}

void MainWindow::openFileDialog() {
    QString filePath = QFileDialog::getOpenFileName(
            this,
            tr("Select APK file"),
            !this->lastOpenPath.isEmpty() ? this->lastOpenPath : QDir::homePath(),
            tr("Android APK file (*.apk)")
    );

    if (!filePath.isEmpty()) {
        QFileInfo finfo(filePath);
        this->lastOpenPath = finfo.absolutePath();
    }

    this->apkPath = filePath;

    this->tmpDir = QDir::tempPath();
    this->tmpDir
            .append("/")
            .append("ade/")
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

void MainWindow::extractFile() {
    if (this->apkPath.isEmpty() || this->apkPath.isNull()) {
        this->showError("Apk file not selected");
        return;
    }


    ApkTool *tool = new ApkTool(this);
    tool->setTemporaryPath(this->tmpDir);
    tool->setApkPath(this->apkPath);

    if (this->ui->clearCache->isChecked()) {
        tool->clearTempDirectory();
    }

    connect(tool, SIGNAL(processOutput(QString, bool)), this, SLOT(writeOutput(QString, bool)));
    connect(tool, SIGNAL(processComplete(QVector<ManifestParser::Link> & )), this,
            SLOT(processComplete(QVector<ManifestParser::Link> & )));
    connect(tool, SIGNAL(processStatus(ApkTool::Status)), this, SLOT(processStatus(ApkTool::Status)));
    this->ui->outDeeplinks->clear();
    tool->parse();
}

void MainWindow::writeOutput(QString s, bool) {
    this->ui->processResult->append(s);
}

void MainWindow::processStatus(ApkTool::Status status) {
    ApkTool *tool = dynamic_cast<ApkTool *>(sender());
    if (status != ApkTool::Status::Success) {
        this->showError(tool->getStatusText(status));
    }
}

void MainWindow::processComplete(QVector<ManifestParser::Link> &deeplinks) {
            foreach(ManifestParser::Link link, deeplinks) {
            this->ui->outDeeplinks->append(link.toString(this->ui->asIntent->isChecked()));
        }
}

int MainWindow::showError(const QString text) {
    QMessageBox m(this);
    m.setWindowTitle("Error");
    m.setText(text);
    m.setStandardButtons(QMessageBox::Ok);
    return m.exec();
}

void MainWindow::setLastOpenPath(QString path) {
    this->lastOpenPath = path;
}

