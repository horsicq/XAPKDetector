[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=NF3FBD3KHMXDN)
[![GitHub tag (latest SemVer)](https://img.shields.io/github/tag/horsicq/XAPKDetector.svg)](https://github.com/horsicq/XAPKDetector/releases)
[![GitHub All Releases](https://img.shields.io/github/downloads/horsicq/XAPKDetector/total.svg)](https://github.com/horsicq/XAPKDetector/releases)
[![gitlocalized ](https://gitlocalize.com/repo/4736/whole_project/badge.svg)](https://gitlocalize.com/repo/4736/whole_project?utm_source=badge)

**XAPKDetector** is Android/APK/DEX detector for Windows, Linux and MacOS.

**XAPKDetector** shows an information about build tools, libraries and protection of APK/DEX files

- Heuristic scan
- String viewer
- Hex viewer
- Entropy viewer
- Hash viewer
- ELF viewer
- DEX raw viewer


![alt text](https://github.com/horsicq/XAPKDetector/blob/master/mascots/version.png "Mascot")

There are two versions of  program.

**xapkd** - GUI version
**xapkc** - console version.

![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/1.png "1")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/2.png "2")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/3.png "3")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/4.png "4")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/5.png "5")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/6.png "6")
![alt text](https://github.com/horsicq/XAPKDetector/blob/master/docs/7.png "7")

How to build on Docker
=======
git clone --recursive https://github.com/horsicq/XAPKDetector.git

cd XAPKDetector

docker build .

How to build on Linux(Debian package)
=======

Install packages:

- sudo apt-get install qtbase5-dev -y
- sudo apt-get install qttools5-dev-tools -y
- sudo apt-get install git -y
- sudo apt-get install build-essential -y
- sudo apt-get install qt5-default -y

git clone --recursive https://github.com/horsicq/XAPKDetector.git

cd XAPKDetector

Run build script: bash -x build_dpkg.sh

Install deb package: sudo dpkg -i release/die_[Version].deb

Run: *xapkd [FileName]* or *xapkdc [FileName]*

How to build on Linux(Automake)
=======

Qt framework has to be installed on the system.

(Ubuntu)Install Qt Framework: sudo apt-get install --quiet --assume-yes build-essential qt5-default qtbase5-dev qttools5-dev-tools

Clone project: git clone --recursive https://github.com/horsicq/XAPKDetector.git

- chmod a+x configure
- ./configure
- make
- sudo make install

Run: *xapkd [FileName]* or *xapkdc [FileName]*

How to build on OSX
=======

Install Qt 5.15.2: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/XAPKDetector.git

Edit build_mac.sh ( check QMAKE_PATH variable)

Run build script: bash -x build_mac.sh

How to build on Windows(XP) with Visual Studio
=======

Install Visual Studio 2013: https://github.com/horsicq/build_tools

Install Qt 5.6.3 for VS2013: https://github.com/horsicq/build_tools

Install 7-Zip: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/XAPKDetector.git

Edit build_msvc_winxp.bat ( check VSVARS_PATH, SEVENZIP_PATH, QMAKE_PATH variables)

Run build_msvc_winxp.bat

How to build on Windows(7-10) with Visual Studio
=======

Install Visual Studio 2019: https://github.com/horsicq/build_tools

Install Qt 5.15.2 for VS2019: https://github.com/horsicq/build_tools

Install 7-Zip: https://github.com/horsicq/build_tools

Install Inno Setup: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/XAPKDetector.git

Edit build_msvc_win32.bat ( check VSVARS_PATH, SEVENZIP_PATH, INNOSETUP_PATH, QMAKE_PATH variables)

Edit build_msvc_win64.bat ( check VSVARS_PATH, SEVENZIP_PATH, INNOSETUP_PATH, QMAKE_PATH variables)

Run build_msvc_win32.bat

Run build_msvc_win64.bat


![alt text](https://github.com/horsicq/XAPKDetector/blob/master/mascots/xapkd.png "Mascot")
