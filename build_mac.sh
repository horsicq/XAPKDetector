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
    make_translate "gui_source_tr.pro" xapkd
    cd "$X_SOURCE_PATH"

    check_file "$X_SOURCE_PATH/build/release/xapkdc"
    check_file "$X_SOURCE_PATH/build/release/xapkd.app/Contents/MacOS/xapkd"
    if [ -z "$X_ERROR" ]; then
        cp -R "$X_SOURCE_PATH/build/release/xapkd.app"    "$X_SOURCE_PATH/release/$X_BUILD_NAME"
        cp -R "$X_SOURCE_PATH/build/release/xapkdc"       "$X_SOURCE_PATH/release/$X_BUILD_NAME/xapkd.app/Contents/MacOS/"

        mkdir -p $X_SOURCE_PATH/release/$X_BUILD_NAME/xapkd.app/Contents/Resources/signatures
        cp -R $X_SOURCE_PATH/signatures/crypto.db       $X_SOURCE_PATH/release/$X_BUILD_NAME/xapkd.app/Contents/Resources/signatures
        cp -Rf $X_SOURCE_PATH/XStyles/qss               $X_SOURCE_PATH/release/$X_BUILD_NAME/xapkd.app/Contents/Resources/

        fiximport "$X_SOURCE_PATH/build/release/xapkd.app/Contents/MacOS/xapkd"
        fiximport "$X_SOURCE_PATH/build/release/xapkd.app/Contents/MacOS/xapkdc"

        deploy_qt_library QtWidgets xapkd
        deploy_qt_library QtGui xapkd
        deploy_qt_library QtCore xapkd
        deploy_qt_library QtDBus xapkd
        deploy_qt_library QtPrintSupport xapkd
        deploy_qt_library QtSvg xapkd
        deploy_qt_library QtOpenGL xapkd
        deploy_qt_library QtConcurrent xapkd

        deploy_qt_plugin platforms libqcocoa xapkd
        deploy_qt_plugin platforms libqminimal xapkd
        deploy_qt_plugin platforms libqoffscreen xapkd
        
        deploy_qt_plugin imageformats qjpeg xapkd
        deploy_qt_plugin imageformats qtiff xapkd
        deploy_qt_plugin imageformats qico xapkd
        deploy_qt_plugin imageformats qgif xapkd

        make_release
        make_clear
    fi
fi