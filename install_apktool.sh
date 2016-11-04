#/bin/bash

echo -e "Downloading installer...\n"
wget https://raw.githubusercontent.com/iBotPeaches/Apktool/master/scripts/osx/apktool

echo -e "Downloading tool...\n"
wget https://bitbucket.org/iBotPeaches/apktool/downloads/apktool_2.2.1.jar
ln -s apktool_2.2.1.jar apktool.jar

chmod +x apktool
chmod +x apktool.jar

