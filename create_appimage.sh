#!/bin/bash -x
export X_SOURCE_PATH=$PWD
export X_RELEASE_VERSION=$(cat "release_version.txt")

source build_tools/linux.sh

create_image_app_dir xapkd

cp -f $X_SOURCE_PATH/build/release/xapkd                            $X_SOURCE_PATH/release/appDir/usr/bin/
cp -f $X_SOURCE_PATH/build/release/xapkdc                           $X_SOURCE_PATH/release/appDir/usr/bin/
cp -f $X_SOURCE_PATH/DEBIAN/xapkd.desktop                           $X_SOURCE_PATH/release/appDir/usr/share/applications/
sed -i "s/#VERSION#/1.0/"                                           $X_SOURCE_PATH/release/appDir/usr/share/applications/xapkd.desktop
cp -Rf $X_SOURCE_PATH/DEBIAN/hicolor/                               $X_SOURCE_PATH/release/appDir/usr/share/icons/
cp -Rf $X_SOURCE_PATH/XStyles/qss/                                  $X_SOURCE_PATH/release/appDir/usr/lib/xapkd/
mkdir -p $X_SOURCE_PATH/release/appDir/usr/lib/xapkd/signatures
cp -f $X_SOURCE_PATH/signatures/crypto.db                           $X_SOURCE_PATH/release/appDir/usr/lib/xapkd/signatures/

cd $X_SOURCE_PATH/release

linuxdeployqt $X_SOURCE_PATH/release/appDir/usr/share/applications/xapkd.desktop -appimage -always-overwrite
mv *.AppImage xapkd_${X_RELEASE_VERSION}.AppImage

cd $X_SOURCE_PATH

rm -Rf $X_SOURCE_PATH/release/appDir
