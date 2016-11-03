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

class FileHelper
{
public:
    FileHelper() = delete;
    ~FileHelper() = delete;

    bool static exists(const QString path);
    bool static isExecutable(const QString path);

private:
#ifdef QT_DEBUG
    const bool static debug = true;
#else
    const bool static debug = false;
#endif
};

#endif // FILEHELPER_H
