[![GitHub tag (latest SemVer)](https://img.shields.io/github/tag/horsicq/XAPKDetector.svg)](https://github.com/horsicq/XAPKDetector/releases)
[![GitHub All Releases](https://img.shields.io/github/downloads/horsicq/XAPKDetector/total.svg)](https://github.com/horsicq/XAPKDetector/releases)
[![gitlocalized ](https://gitlocalize.com/repo/4736/whole_project/badge.svg)](https://gitlocalize.com/repo/4736/whole_project?utm_source=badge)

XAPKDetector is Android/APK/DEX detector for Windows, Linux and MacOS.

XAPKDetector shows an information about build tools, libraries and protection of APK/DEX files

- Heuristic scan
- String viewer
- Hex viewer
- Entropy viewer
- Hash viewer
- ELF viewer
- DEX raw viewer


![alt text](https://github.com/horsicq/XAPKDetector/blob/master/mascots/version.jpg "Mascot")

There are two versions of  program.

**xad** - GUI version
**xadc** - console version.

![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/1.png "1")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/2.png "2")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/3.png "3")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/4.png "4")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/5.png "5")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/6.png "6")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/7.png "7")

How to build on Linux
=======

Install Qt 5.15.1: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/XAPKDetector.git

Edit build_lin64.bat ( check QT_PATH variable)

Run build_lin64.bat

How to build on OSX
=======

Install Qt 5.15.1: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/XAPKDetector.git

Edit build_mac.bat ( check QT_PATH variable)

Run build_mac.bat

How to build on Windows(XP)
=======

Install Visual Studio 2013: https://github.com/horsicq/build_tools

Install Qt 5.6.3 for VS2013: https://github.com/horsicq/build_tools

Install 7-Zip: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/XAPKDetector.git

Edit build_winxp.bat ( check VS_PATH,  SEVENZIP_PATH, QT_PATH variables)

Run build_winxp.bat

How to build on Windows(7-10)
=======

Install Visual Studio 2019: https://github.com/horsicq/build_tools

Install Qt 5.15.1 for VS2019: https://github.com/horsicq/build_tools

Install 7-Zip: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/XAPKDetector.git

Edit build_win64.bat ( check VS_PATH,  SEVENZIP_PATH, QT_PATH variables)

Run build_win64.bat

![alt text](https://github.com/horsicq/XAPKDetector/blob/master/mascots/xad.jpg "Mascot")
