/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2016 					                               *
 *   https://github.com/edwardstock										   *
 *   Author: Eduard Maximovich <edward.vstock@gmail.com>				   *
 *                                                                         *
 ***************************************************************************/

#include "FileHelper.h"

bool FileHelper::exists(const QString path)
{
    bool exists = QFile(path).exists();
    if (debug) {
        qDebug() << "File exists: " << path << " - " << (exists ? "true" : "false");
    }

    return exists;
}

bool FileHelper::isExecutable(const QString path)
{
    QFile f(path);
    bool isEx = (f.permissions() & QFile::Permission::ExeUser) > 0;
    if (debug) {
        qDebug() << "File executable: " << path << " - " << (isEx ? "true" : "false");
    }

    return isEx;
}
