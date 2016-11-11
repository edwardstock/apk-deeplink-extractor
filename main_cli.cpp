/**
 * ApkDeeplinkExtractor
 * main_cli.cpp
 *
 * @author Eduard Maximovich <edward.vstock@gmail.com>
 * @link https://github.com/edwardstock
 * @copyright 2016 GNU General Public License v3
 */

#include <QCoreApplication>
#include <QTimer>
#include "app/cli/CliParser.h"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    CliParser parser(&a);

    QCoreApplication::setApplicationName(VER_INTERNALNAME_STR);
    QCoreApplication::setApplicationVersion(VER_PRODUCTVERSION_STR);

    QTimer::singleShot(0, &parser, SLOT(run()));

    return a.exec();
}
