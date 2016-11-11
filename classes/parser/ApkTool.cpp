/**
 * ApkDeeplinkExtractor
 * ApkTool.cpp
 *
 * @author Eduard Maximovich <edward.vstock@gmail.com>
 * @link https://github.com/edwardstock
 * @copyright 2016 GNU General Public License v3
 */
#include "ApkTool.h"

const QString ApkTool::statusMessages[] = {
        "Success",
        "Deeplinks not found",
        "Apktool script not found",
        "Apk file not defined",
        "Extract failed with non success exit code",
        "Error while parsing manifest file",
};

ApkTool::ApkTool(QObject *_parent) : QObject(_parent) {
    this->tmpDir = QString();
    this->deeplinks = QVector<ManifestParser::Link>();
    this->process = NULL;
}

ApkTool::~ApkTool() {
    if (process != NULL) {
        delete process;
    }
}

void ApkTool::extract() {
    if (!(this->apkPath.isNull() || !this->apkPath.isEmpty())) {
        emit processStatus(Status::ApkFileNotDefined);
        return;
    }

    if (this->tmpDir.isEmpty()) {
        this->tmpDir = QDir::tempPath();
    }

    // apk already extracted
    if (QFile(getManifestPath()).exists()) {
        runParse(0, QProcess::ExitStatus::NormalExit);
        return;
    }

    QString command = getExecutor();
    Status buildArgumentsStatus;
    QStringList arguments = buildArguments(&buildArgumentsStatus);

    if (buildArgumentsStatus != Status::Success) {
        emit processStatus(buildArgumentsStatus);
        return;
    }

    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->start(getExecutor(), arguments);
    process->waitForStarted();

    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(writeOutput()));
    connect(process,
            SIGNAL(finished(int, QProcess::ExitStatus)),
            this,
            SLOT(runParse(int, QProcess::ExitStatus))
    );
}

void ApkTool::writeOutput() {
    Q_ASSERT(this->process != nullptr);
    emit processOutput(this->process->readAllStandardOutput(), false);
    emit processOutput(this->process->readAllStandardError(), true);
}

void ApkTool::parse() {
    extract();
}

QString ApkTool::getExecutor() const {
    return QString(SYS_EX);
}

QStringList ApkTool::buildArguments(Status *status) {
    QStringList arguments;
    QString execArg = (QString &&) QDir::currentPath().append("/").append(EXECUTABLE);

    if (!FileHelper::exists(execArg)) {
        *status = Status::ApktoolNotFound;
        return arguments;
    }

    if (QString(SYS_EX_ARG) != "") {
        arguments << SYS_EX_ARG;
    }

    arguments << execArg;
    arguments << "d" << this->apkPath;
    arguments << "-f";
    arguments << "--output" << this->tmpDir;

    *status = Status::Success;
    return arguments;
}

QString ApkTool::getManifestPath() {
    return QString(this->tmpDir).append("/AndroidManifest.xml");
}

ApkTool &ApkTool::setApkPath(QString path) {
    this->apkPath = path;
    return *this;
}

ApkTool &ApkTool::setTemporaryPath(QString path) {
    this->tmpDir = path;
    return *this;
}

void ApkTool::runParse(int exitCode, QProcess::ExitStatus) {
    if (exitCode != 0) {
        emit processOutput("Extract failed", true);
        return;
    }

    ManifestParser parser(getManifestPath());

    if (!parser.parse()) {
        if (parser.getStatus() == ManifestParser::Success) {
            emit processStatus(Status::DeeplinksNotFound);
        } else {
            emit processStatus(Status::ParseError);
            emit processOutput(parser.getStatusText(), true);
        }
        return;
    } else {
        deeplinks = parser.getDeeplinks();
    }

    emit processStatus(Status::Success);
    emit processOutput("Extracting complete", false);
    emit processComplete(deeplinks);
}

bool ApkTool::clearTempDirectory() {
    QDir dir(this->tmpDir);
    return dir.removeRecursively();
}

QString ApkTool::getStatusText(ApkTool::Status status) {
    return statusMessages[status];
}




