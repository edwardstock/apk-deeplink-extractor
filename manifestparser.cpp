/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2016 					                               *
 *   https://github.com/edwardstock										   *
 *   Author: Eduard Maximovich <edward.vstock@gmail.com>				   *
 *                                                                         *
 ***************************************************************************/

#include "manifestparser.h"

ManifestParser::ManifestParser(const QString &manifestPath)
{
    this->path = new QFile(manifestPath);

    if(!this->path->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open manifest";
        loaded = false;
    }
}

ManifestParser::~ManifestParser()
{
    delete path;
}

bool ManifestParser::parse()
{
    if(!this->loaded) {
        return false;
    }

    QString xml = this->path->readAll();
    QString pattern("data android:host=\"([a-zA-Z0-9-_\\.\\/\\\\]+)\"\\sandroid:scheme=\"([a-zA-Z0-9-_\\.\\/\\\\]+)\".*");

    QRegularExpression rx(pattern);
    rx.setPatternOptions(QRegularExpression::PatternOption::MultilineOption | QRegularExpression::PatternOption::CaseInsensitiveOption | QRegularExpression::PatternOption::UseUnicodePropertiesOption);

    QRegularExpressionMatchIterator result = rx.globalMatch(xml);

    int found = 0;
    while(result.hasNext()) {
        QRegularExpressionMatch m = result.next();

        Link link;
        link.scheme = m.captured(2);
        link.route = m.captured(1);
        if(link.scheme == "http" || link.scheme == "https") continue;
        deeplinks.push_back(link);
        found++;
    }

    xml.clear();

    return found > 0;
}

bool ManifestParser::manifestLoaded()
{
    return this->loaded;
}

QVector<ManifestParser::Link> ManifestParser::getDeeplinks()
{
    return this->deeplinks;
}
