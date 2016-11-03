/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2016 					                               *
 *   https://github.com/edwardstock										   *
 *   Author: Eduard Maximovich <edward.vstock@gmail.com>				   *
 *                                                                         *
 ***************************************************************************/

#ifndef MANIFESTPARSER_H
#define MANIFESTPARSER_H

#include <QString>
#include <QFile>
#include <QVector>
#include <QDebug>
#include <QRegularExpression>

class ManifestParser
{
public:
    typedef struct Link
    {
        QString scheme;
        QString route;
    } Link;

    ManifestParser(const QString &manifestPath);
    ~ManifestParser();

    QVector<Link> getDeeplinks();
    bool parse();
    bool manifestLoaded();
private:
    QFile *path;
    QVector<Link> deeplinks;
    bool loaded = true;
};

#endif // MANIFESTPARSER_H
