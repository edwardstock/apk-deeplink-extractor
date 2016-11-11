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
    typedef struct Link {
    private:
        QString _intent;
    public:
        Link()
                : _intent(QString()) {}

        QString packageId;
        QString scheme;
        QString route;

        QString &toString(bool asIntent = false) {
            if (!asIntent) {
                return scheme.append("://").append(route);
            }

            if (!_intent.isEmpty()) {
                return _intent;
            }

            QStringList intent;
            intent << QString("intent://") + route + QString("#Intent");
            intent << QString("scheme=") + scheme;
            intent << "package=" + packageId;
            intent << QString("S.browser_fallback_url=") + QString("market://details?id=") + packageId;
            intent << "end";

            _intent = intent.join(";");

            return _intent;

        }
    } Link;

    enum Status {
        Success,
        EmptyManifest,
    };

    explicit ManifestParser(const QString &manifestPath);

    ManifestParser(ManifestParser &that);

    ~ManifestParser();

    QVector<Link> getDeeplinks();

    bool parse();

    bool manifestLoaded();

    ManifestParser::Status getStatus();

    QString getStatusText();

private:
    static const QString statusMessages[];
    Status status;
    QFile *path;
    QVector<Link> deeplinks;
};

#endif // MANIFESTPARSER_H
