/**
 * ApkDeeplinkExtractor
 * ManifestParser.cpp
 *
 * @author Eduard Maximovich <edward.vstock@gmail.com>
 * @link https://github.com/edwardstock
 * @copyright 2016 GNU General Public License v3
 */

#include "ManifestParser.h"

const QString ManifestParser::statusMessages[] = {
    "Success",
    "Manifest file not found or empty"
};

ManifestParser::ManifestParser(const QString &manifestPath) :
    status(Status::Success) {
    this->path = new QFile(manifestPath);
    this->deeplinks = QVector<Link>();

    if (!this->path->open(QIODevice::ReadOnly | QIODevice::Text) || this->path->size() == 0) {
        status = Status::EmptyManifest;
    }
}

ManifestParser::ManifestParser(ManifestParser &that) :
    status(that.status),
    deeplinks(that.deeplinks) {
    this->path = new QFile(that.path->fileName());
}

ManifestParser::~ManifestParser() {
    delete path;
}

bool ManifestParser::parse() {
    if (!manifestLoaded()) {
        return false;
    }

    QString xml = this->path->readAll();
    QString pattern(
        "android:(scheme|host)=\"([a-zA-Z0-9-_\\.\\/\\\\]+)\"\\s+android:(scheme|host)=\"([a-zA-Z0-9-_\\.\\/\\\\]+)\"|android:(scheme)=\"([a-zA-Z0-9-_\\.\\/\\\\]+)\""
    );

    QRegularExpression rx(pattern);
    rx.setPatternOptions(
        QRegularExpression::PatternOption::MultilineOption
            | QRegularExpression::PatternOption::CaseInsensitiveOption
            | QRegularExpression::PatternOption::UseUnicodePropertiesOption
    );

    QRegularExpressionMatchIterator result = rx.globalMatch(xml);

    QRegularExpression rxPackage("package=\"([a-zA-Z0-9_\\-\\.]+)\"");
    QRegularExpressionMatch packageMatch = rxPackage.match(xml);
    QString packageId;
    if (packageMatch.hasMatch()) {
        packageId = packageMatch.captured(1);
    }

    int found = 0;

    while (result.hasNext()) {
        QRegularExpressionMatch m = result.next();

        Link link;
        link.packageId = packageId;

        QString scheme, route;

        if (!m.captured(5).isNull() && !m.captured(6).isNull()) {
            scheme = m.captured(6);
        } else if (!m.captured(1).isNull() && !m.captured(2).isNull() && !m.captured(3).isNull()
            && !m.captured(4).isNull()) {
            if (m.captured(1) == "host") {
                route = m.captured(2);
                scheme = m.captured(4);
            } else {
                route = m.captured(4);
                scheme = m.captured(2);
            }
        } else {
            continue;
        }

        link.scheme = scheme;
        link.route = route;

        if (
            link.scheme == "http"
                || link.scheme == "https"
                || link.scheme == "file"
                || link.scheme == "package"
                || link.scheme == "sms"
                || link.scheme == "smsto"
            )
            continue;

        deeplinks.push_back(link);
        found++;
    }

    xml.clear();

    return found > 0;
}

bool ManifestParser::manifestLoaded() {
    return status != Status::EmptyManifest;
}

QVector<ManifestParser::Link> ManifestParser::getDeeplinks() {
    return this->deeplinks;
}

ManifestParser::Status ManifestParser::getStatus() {
    return status;
}

QString ManifestParser::getStatusText() {
    return statusMessages[this->status];
}
