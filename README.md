# apk-deeplink-extractor
GUI and CLI Tool for extracting deeplink schemas from android manifest file, using apktool

[![Build Status](https://travis-ci.org/edwardstock/apk-deeplink-extractor.svg?branch=master)](https://travis-ci.org/edwardstock/apk-deeplink-extractor)

## Latest release 1.1.0
* macOS (min 10.7): [dmg](https://github.com/edwardstock/apk-deeplink-extractor/releases/download/1.1.0/ade_image_1.1.0.dmg)
* win32(64) installer: [installer](https://github.com/edwardstock/apk-deeplink-extractor/releases/download/1.1.0/ade_installer_win32_1.1.0.exe)

## Building
### Requirements
* Qt5.2+ including qmake. GUI(Core, Gui, Widgets); CLI(Core)
* Java runtime or JDK or OpenJDK >= 7
* make

#### Build GUI
```bash
qmake apk_deeplink_extractor.pro
make
make install
```

#### Build CLI tool
```bash
qmake apk_deeplink_extractor.pro "CONFIG+=console"
make
make install
```

CLI tool usage (Reading directly manifest not implemented yet!)
```bash
Usage: ./ApkDeeplinkExtractor [options] source
Tool for extracting deeplink schemas from android manifest file, using apktool

Options:
  -h, --help          Displays this help.
  -v, --version       Displays version information.
  -j, --json          Show list as json array
  -i, --intent        Show deeplinks as chrome intent
  -o, --output        Directory where will extracted apk file. Default: /tmp
  -f, --overwriteAll  Clear all data in temporary output directory (if apk selected)

Arguments:
  source              Apk file path or AndroidManifest.xml
```


