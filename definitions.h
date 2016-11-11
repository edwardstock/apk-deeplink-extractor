/**
 * ApkDeeplinkExtractor
 * definitions.h
 *
 * @author Eduard Maximovich <edward.vstock@gmail.com>
 * @link https://github.com/edwardstock
 * @copyright 2016 GNU General Public License v3
 */

#ifndef APKDEEPLINKEXTRACTOR_DEFINITIONS_H
#define APKDEEPLINKEXTRACTOR_DEFINITIONS_H


#if _WIN64 || _WIN32
#define EXECUTABLE "apktool.bat"
#define SYS_EX "cmd.exe"
#define SYS_EX_ARG "/c"
#elif __APPLE__ && __MACH__ && !defined(ADE_CLI)
#define EXECUTABLE "../Resources/apktool" // package resource dir
#define SYS_EX "/bin/sh"
#define SYS_EX_ARG ""
#else // osx or linux, not matter
#define EXECUTABLE "apktool"
#define SYS_EX "/bin/sh"
#define SYS_EX_ARG ""
#endif

#endif //APKDEEPLINKEXTRACTOR_DEFINITIONS_H
