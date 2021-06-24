#!/bin/bash -x
export X_SOURCE_PATH=$PWD

cp -f $X_SOURCE_PATH/build/release/xapkd                            /usr/bin/
cp -f $X_SOURCE_PATH/build/release/xapkdc                           /usr/bin/
cp -f $X_SOURCE_PATH/DEBIAN/xapkd.desktop                           /usr/share/applications/
cp -Rf $X_SOURCE_PATH/DEBIAN/hicolor/                               /usr/share/icons/
cp -Rf $X_SOURCE_PATH/XStyles/qss/                                  /usr/lib/xapkd/
mkdir -p  /usr/lib/xapkd/signatures
cp -f $X_SOURCE_PATH/signatures/crypto.db                           /usr/lib/xapkd/signatures/
