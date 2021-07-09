set MINGWVARS_PATH="C:\Qt\5.15.2\mingw81_32\bin\qtenv2.bat"
set QMAKE_PATH="qmake.exe"
set SEVENZIP_PATH="C:\Program Files\7-Zip\7z.exe"

set X_SOURCE_PATH=%~dp0
set X_BUILD_NAME=xapkdetector_mingw_win32_portable
set /p X_RELEASE_VERSION=<%X_SOURCE_PATH%\release_version.txt

call %X_SOURCE_PATH%\build_win_generic.cmd