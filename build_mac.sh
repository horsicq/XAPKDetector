#!/bin/sh -x
export QMAKE_PATH=$HOME/Qt/5.15.2/clang_64/bin/qmake

export X_SOURCE_PATH=$PWD
export X_BUILD_NAME=xapkdetector_mac_portable
export X_RELEASE_VERSION=$(cat "release_version.txt")

source build_tools/mac.sh

check_file $QMAKE_PATH

if [ -z "$X_ERROR" ]; then
    make_init
    make_build "$X_SOURCE_PATH/xapkdetector_source.pro"
    cd "$X_SOURCE_PATH/gui_source"
    make_translate "gui_source_tr.pro" xad
    cd "$X_SOURCE_PATH"

    check_file "$X_SOURCE_PATH/build/release/xadc"
    check_file "$X_SOURCE_PATH/build/release/xad.app/Contents/MacOS/xad"
    if [ -z "$X_ERROR" ]; then
        cp -R "$X_SOURCE_PATH/build/release/xad.app"    "$X_SOURCE_PATH/release/$X_BUILD_NAME"
        cp -R "$X_SOURCE_PATH/build/release/xadc"       "$X_SOURCE_PATH/release/$X_BUILD_NAME/xad.app/Contents/MacOS/"

        mkdir -p $X_SOURCE_PATH/release/$X_BUILD_NAME/xad.app/Contents/Resources/signatures
        cp -R $X_SOURCE_PATH/signatures/crypto.db       $X_SOURCE_PATH/release/$X_BUILD_NAME/xad.app/Contents/Resources/signatures
        cp -Rf $X_SOURCE_PATH/XStyles/qss               $X_SOURCE_PATH/release/$X_BUILD_NAME/xad.app/Contents/Resources/

        fiximport "$X_SOURCE_PATH/build/release/xad.app/Contents/MacOS/xad"
        fiximport "$X_SOURCE_PATH/build/release/xad.app/Contents/MacOS/xadc"

        deploy_qt_library QtWidgets xad
        deploy_qt_library QtGui xad
        deploy_qt_library QtCore xad
        deploy_qt_library QtDBus xad
        deploy_qt_library QtPrintSupport xad
        deploy_qt_library QtSvg xad
        deploy_qt_library QtOpenGL xad
        deploy_qt_library QtConcurrent xad

        deploy_qt_plugin platforms libqcocoa xad
        deploy_qt_plugin platforms libqminimal xad
        deploy_qt_plugin platforms libqoffscreen xad
        
        deploy_qt_plugin imageformats qjpeg xad
        deploy_qt_plugin imageformats qtiff xad
        deploy_qt_plugin imageformats qico xad
        deploy_qt_plugin imageformats qgif xad

        make_release
        make_clear
    fi
fi