/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2016 					                               *
 *   https://github.com/edwardstock										   *
 *   Author: Eduard Maximovich <edward.vstock@gmail.com>				   *
 *                                                                         *
 ***************************************************************************/

#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QFile>
#include <QString>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

class FileHelper {
public:
    FileHelper() = delete;

    ~FileHelper() = delete;

    bool static exists(const QString path);

    bool static isExecutable(const QString path);

    bool static getExtension(QString source, QString *result);

    bool static getExtension(QFile source, QString *result);
};

#endif // FILEHELPER_H
