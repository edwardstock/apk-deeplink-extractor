/**
 * ApkDeeplinkExtractor
 * FileHelper.h
 *
 * @author Eduard Maximovich <edward.vstock@gmail.com>
 * @link https://github.com/edwardstock
 * @copyright 2016 GNU General Public License v3
 */

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
