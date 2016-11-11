/**
 * ApkDeeplinkExtractor
 * FileHelper.cpp
 *
 * @author Eduard Maximovich <edward.vstock@gmail.com>
 * @link https://github.com/edwardstock
 * @copyright 2016 GNU General Public License v3
 */

#include "FileHelper.h"

bool FileHelper::exists(const QString path) {
    return QFile(path).exists();
}

bool FileHelper::isExecutable(const QString path) {
    QFile f(path);
    return (f.permissions() & QFile::Permission::ExeUser) > 0;
}

bool FileHelper::getExtension(QString source, QString *result) {
    QRegularExpression extReg("^.*\\.((xml|apk)+)$");
    QRegularExpressionMatch match = extReg.match(source);
    if (!match.hasMatch()) {
        return false;
    }
    *result = match.captured(1);
    return true;
}

bool FileHelper::getExtension(QFile source, QString *result) {
    return getExtension(source.fileName(), result);
}
