set VSVARS_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"
set QMAKE_PATH="C:\Qt\5.15.2\msvc2019\bin\qmake.exe"
set SEVENZIP_PATH="C:\Program Files\7-Zip\7z.exe"

set X_SOURCE_PATH=%~dp0
set X_BUILD_NAME=xapkdetector_win32_portable
set /p X_RELEASE_VERSION=<%X_SOURCE_PATH%\release_version.txt

call %X_SOURCE_PATH%\build_win_generic.cmd