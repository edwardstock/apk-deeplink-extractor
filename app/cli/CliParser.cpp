/**
 * ApkDeeplinkExtractor
 * CliParser.cpp
 *
 * @author Eduard Maximovich <edward.vstock@gmail.com>
 * @link https://github.com/edwardstock
 * @copyright 2016 GNU General Public License v3
 */

#include "CliParser.h"

CliParser::CliParser(QObject *_parent) :
        QObject(_parent),
        manifestParser(NULL), apkTool(NULL) {
    this->app = dynamic_cast<QCoreApplication *>(_parent);
}

CliParser::~CliParser() {
    if (this->manifestParser != NULL) {
        delete this->manifestParser;
    }

    if (this->apkTool != NULL) {
        delete this->apkTool;
    }
}

void CliParser::run() {
    QCommandLineParser parser;
    parser.setApplicationDescription("Tool for extracting deeplink schemas from android manifest file, using apktool");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("source", "Apk file path or AndroidManifest.xml");
    QCommandLineOption asJsonOpt(QStringList() << "j" << "json", "Show list as json array");
    QCommandLineOption asIntentOpt(QStringList() << "i" << "intent", "Show deeplinks as chrome intent");
    QCommandLineOption
            tmpDirOpt(QStringList() << "o" << "output", "Directory where will extracted apk file. Default: /tmp");
    QCommandLineOption overwriteAllOpt
            (QStringList() << "f" << "overwriteAll", "Clear all data in temporary output directory (if apk selected)");
    parser.addOption(asJsonOpt);
    parser.addOption(asIntentOpt);
    parser.addOption(tmpDirOpt);
    parser.addOption(overwriteAllOpt);

    parser.process(*this->app);

    QStringList args = parser.positionalArguments();
    if (args.size() < 1) {
        cerr << "Source is not set" << endl;
        QCoreApplication::exit(EXIT_FAILURE);
        return;
    }

    QString source = args.at(0);
    if (source.isNull() || source.isEmpty()) {
        cerr << "Source is not set" << endl;
        QCoreApplication::exit(EXIT_FAILURE);
        return;
    }

    this->asJson = parser.isSet(asJsonOpt);
    this->asIntent = parser.isSet(asIntentOpt);
    bool clearTemp = parser.isSet(overwriteAllOpt);
    QString extension;
    if (!FileHelper::getExtension(source, &extension)) {
        cerr << "Unknown source file passed " << source.toStdString() << endl;
        QCoreApplication::exit(EXIT_FAILURE);
        return;
    }

    if (extension.toLower() == "apk") {
        this->tmpDir = parser.value(tmpDirOpt);
        if (this->tmpDir.isEmpty() || this->tmpDir.isNull()) {
            this->tmpDir = DEFAULT_TEMP_DIR;
            if (clearTemp) {
                QDir(this->tmpDir).removeRecursively();
            }

            this->tmpDir.append(
                    QCryptographicHash::hash((source.toLocal8Bit()), QCryptographicHash::Md5).toHex()
            );
        } else {
            if (clearTemp) {
                QDir(this->tmpDir).removeRecursively();
            }
        }

        this->parseApk(source);
    } else if (extension.toLower() == "xml") {
        this->parseManifest();
    } else {
        cerr << "Unsupported source file passed " << source.toStdString() << "; ext: " << extension.toStdString()
             << endl;
        QCoreApplication::exit(EXIT_FAILURE);
    }
}

QVector<ManifestParser::Link> CliParser::parseManifest() {
    return QVector<ManifestParser::Link>();
}

void CliParser::processOutput(QString output, bool error) {
    if (this->asJson) {
        return;
    }

    if (error) {
        cerr << output.toStdString() << endl;
    } else {
        cout << output.toStdString() << endl;
    }
}

void CliParser::processStatus(ApkTool::Status status) {
    ApkTool *tool = dynamic_cast<ApkTool *>(sender());
    if (status != ApkTool::Status::Success) {
        if (status == ApkTool::Status::DeeplinksNotFound && this->asJson) {
            cout << "[]" << endl;
            QCoreApplication::exit(EXIT_FAILURE);
        }
        cerr << "Error " << tool->getStatusText(status).toStdString() << endl;
        QCoreApplication::exit(EXIT_FAILURE);
    } else {
        if (!this->asJson) {
            cout << tool->getStatusText(status).toStdString() << endl;
        }
    }
}

void CliParser::processComplete(QVector<ManifestParser::Link> &deeplinks) {
    this->formatOutput(deeplinks);
    QCoreApplication::exit(EXIT_SUCCESS);
}

void CliParser::parseApk(QString &source) {
    ApkTool *tool = new ApkTool(this);
    tool->setTemporaryPath(this->tmpDir);
    tool->setApkPath(source);

    connect(tool, SIGNAL(processOutput(QString, bool)), this, SLOT(processOutput(QString, bool)));
    connect(tool, SIGNAL(processStatus(ApkTool::Status)), this, SLOT(processStatus(ApkTool::Status)));
    connect(tool,
            SIGNAL(processComplete(QVector<ManifestParser::Link> & )),
            this,
            SLOT(processComplete(QVector<ManifestParser::Link> & )));

    tool->parse();
}

void CliParser::formatOutput(QVector<ManifestParser::Link> &links) {
    if (!this->asJson) {
                foreach(ManifestParser::Link link, links) {
                cout << link.toString(this->asIntent).toStdString() << endl;
            }
        return;
    }

    QJsonDocument doc;
    QJsonArray jsonArray;
            foreach(ManifestParser::Link link, links) {
            jsonArray << link.toString(this->asIntent);
        }

    doc.setArray(jsonArray);

    cout << doc.toJson().toStdString() << endl;
}
