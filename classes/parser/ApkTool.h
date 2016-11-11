/**
 * ApkDeeplinkExtractor
 * ApkTool.h
 *
 * @author Eduard Maximovich <edward.vstock@gmail.com>
 * @link https://github.com/edwardstock
 * @copyright 2016 GNU General Public License v3
 */

#ifndef APKDEEPLINKEXTRACTOR_APKTOOL_H
#define APKDEEPLINKEXTRACTOR_APKTOOL_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QFile>
#include <QDir>
#include <QVector>
#include "definitions.h"
#include "classes/helpers/FileHelper.h"
#include "ManifestParser.h"

class ApkTool : public QObject {
Q_OBJECT

public:
    typedef ManifestParser::Link Deeplink;
    enum Status {
        Success,
        DeeplinksNotFound,
        ApktoolNotFound,
        ApkFileNotDefined,
        ExtractFailed,
        ParseError,
    };

    Q_ENUM(Status);

    explicit ApkTool(QObject *_parent);

    ApkTool(ApkTool &that) = delete;

    ~ApkTool();

    inline QString getManifestPath();

    ApkTool &setApkPath(QString path);

    ApkTool &setTemporaryPath(QString path);

    void parse();

    bool clearTempDirectory();

    QString getStatusText(ApkTool::Status status);

signals:

    void processOutput(QString string, bool error = false);

    void processComplete(QVector<ManifestParser::Link> &deeplinks);

    void processStatus(ApkTool::Status status);

private:
    static const QString statusMessages[];
    QString apkPath;
    QString tmpDir;
    QProcess *process;
    QVector<Deeplink> deeplinks;

    void extract();

    QString getExecutor() const;

    QStringList buildArguments(Status *status);

private slots:

    void writeOutput();

    void runParse(int, QProcess::ExitStatus);

};

#endif //APKDEEPLINKEXTRACTOR_APKTOOL_H
