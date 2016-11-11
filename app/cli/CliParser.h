/**
 * ApkDeeplinkExtractor
 * CliParser.h
 *
 * @author Eduard Maximovich <edward.vstock@gmail.com>
 * @link https://github.com/edwardstock
 */

#ifndef APKDEEPLINKEXTRACTOR_CLIPARSER_H
#define APKDEEPLINKEXTRACTOR_CLIPARSER_H

#include <iostream>
#include <csignal>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QMimeType>
#include <QMetaEnum>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QCryptographicHash>
#include "classes/parser/ManifestParser.h"
#include "classes/parser/ApkTool.h"
#include "classes/helpers/FileHelper.h"
#include "definitions.h"
#include "version.h"

#define DEFAULT_TEMP_DIR "/tmp/ade/"

using namespace std;

class CliParser : public QObject {
Q_OBJECT

public:
    explicit CliParser(QObject *_parent);

    ~CliParser();

    // copy disabled, cause app must be created one time
    CliParser(const CliParser &that) = delete;

public slots:

    void run();

private slots:

    void processOutput(QString output, bool error);

    void processStatus(ApkTool::Status status);

    void processComplete(QVector<ManifestParser::Link> &deeplinks);

private:
    QCoreApplication *app;
    ManifestParser *manifestParser;
    ApkTool *apkTool;
    QString tmpDir;
    bool asJson = false;
    bool asIntent = true;

    QVector<ManifestParser::Link> parseManifest();

    void parseApk(QString &source);

    void formatOutput(QVector<ManifestParser::Link> &links);


};

#endif //APKDEEPLINKEXTRACTOR_CLIPARSER_H
