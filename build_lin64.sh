#!/bin/bash -x
QT_PATH=$HOME/Qt/5.15.1/gcc_64
RELEASE_VERSION=$(cat "release_version.txt")
echo $RELEASE_VERSION
SOURCE_PATH=$PWD

BUILD_NAME=xapkdetector_lin64_portable
GUIEXE=xad
CONEXE=xadc

cd $SOURCE_PATH

function makeproject
{
    cd $SOURCE_PATH/$1
    
    $QT_PATH/bin/qmake $1.pro -spec linux-g++
    make -f Makefile clean
    make -f Makefile

    rm -rf Makefile
    rm -rf Makefile.Release
    rm -rf Makefile.Debug
    rm -rf object_script.*     

    cd $SOURCE_PATH
}

rm -rf $SOURCE_PATH/build

makeproject build_libs
makeproject gui_source
makeproject console_source

mkdir -p release
rm -rf release/$BUILD_NAME
mkdir -p release/$BUILD_NAME
mkdir -p release/$BUILD_NAME/base
mkdir -p release/$BUILD_NAME/base/platforms
mkdir -p release/$BUILD_NAME/base/imageformats

cp -R $QT_PATH/plugins/platforms/libqxcb.so                     $SOURCE_PATH/release/$BUILD_NAME/base/platforms/
cp -R $QT_PATH/plugins/imageformats/libqjpeg.so                 $SOURCE_PATH/release/$BUILD_NAME/base/imageformats/
cp -R $QT_PATH/plugins/imageformats/libqtiff.so                 $SOURCE_PATH/release/$BUILD_NAME/base/imageformats/
cp -R $QT_PATH/plugins/imageformats/libqico.so                  $SOURCE_PATH/release/$BUILD_NAME/base/imageformats/
cp -R $QT_PATH/plugins/imageformats/libqgif.so                  $SOURCE_PATH/release/$BUILD_NAME/base/imageformats/

cp -R $SOURCE_PATH/build/release/xad                            $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $SOURCE_PATH/build/release/xadc                           $SOURCE_PATH/release/$BUILD_NAME/base/

cp -R $QT_PATH/lib/libQt5Core.so.5.15.1                         $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libQt5Gui.so.5.15.1                          $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libQt5Widgets.so.5.15.1                      $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libQt5OpenGL.so.5.15.1                       $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libQt5DBus.so.5.15.1                         $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libQt5XcbQpa.so.5.15.1                       $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libicui18n.so.56.1                           $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libicuuc.so.56.1                             $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libicudata.so.56.1                           $SOURCE_PATH/release/$BUILD_NAME/base/

mv $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Core.so.5.15.1               $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Core.so.5
mv $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Gui.so.5.15.1                $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Gui.so.5
mv $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Widgets.so.5.15.1            $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Widgets.so.5
mv $SOURCE_PATH/release/$BUILD_NAME/base/libQt5OpenGL.so.5.15.1             $SOURCE_PATH/release/$BUILD_NAME/base/libQt5OpenGL.so.5
mv $SOURCE_PATH/release/$BUILD_NAME/base/libQt5DBus.so.5.15.1               $SOURCE_PATH/release/$BUILD_NAME/base/libQt5DBus.so.5
mv $SOURCE_PATH/release/$BUILD_NAME/base/libQt5XcbQpa.so.5.15.1             $SOURCE_PATH/release/$BUILD_NAME/base/libQt5XcbQpa.so.5
mv $SOURCE_PATH/release/$BUILD_NAME/base/libicui18n.so.56.1                 $SOURCE_PATH/release/$BUILD_NAME/base/libicui18n.so.56
mv $SOURCE_PATH/release/$BUILD_NAME/base/libicuuc.so.56.1                   $SOURCE_PATH/release/$BUILD_NAME/base/libicuuc.so.56
mv $SOURCE_PATH/release/$BUILD_NAME/base/libicudata.so.56.1                 $SOURCE_PATH/release/$BUILD_NAME/base/libicudata.so.56

mkdir -p $SOURCE_PATH/release/$BUILD_NAME/base/lang
cp -Rf $SOURCE_PATH/XStyles/qss/ $SOURCE_PATH/release/$BUILD_NAME/base/qss/

$QT_PATH/bin/lrelease  $SOURCE_PATH/gui_source/translation/xad_de.ts -qm    $SOURCE_PATH/release/$BUILD_NAME/base/lang/xad_de.qm
$QT_PATH/bin/lrelease  $SOURCE_PATH/gui_source/translation/xad_ja.ts -qm    $SOURCE_PATH/release/$BUILD_NAME/base/lang/xad_ja.qm
$QT_PATH/bin/lrelease  $SOURCE_PATH/gui_source/translation/xad_pl.ts -qm    $SOURCE_PATH/release/$BUILD_NAME/base/lang/xad_pl.qm
$QT_PATH/bin/lrelease  $SOURCE_PATH/gui_source/translation/xad_pt_BR.ts -qm $SOURCE_PATH/release/$BUILD_NAME/base/lang/xad_pt_BR.qm
$QT_PATH/bin/lrelease  $SOURCE_PATH/gui_source/translation/xad_fr.ts -qm    $SOURCE_PATH/release/$BUILD_NAME/base/lang/xad_fr.qm
$QT_PATH/bin/lrelease  $SOURCE_PATH/gui_source/translation/xad_ru.ts -qm    $SOURCE_PATH/release/$BUILD_NAME/base/lang/xad_ru.qm
$QT_PATH/bin/lrelease  $SOURCE_PATH/gui_source/translation/xad_vi.ts -qm    $SOURCE_PATH/release/$BUILD_NAME/base/lang/xad_vi.qm
$QT_PATH/bin/lrelease  $SOURCE_PATH/gui_source/translation/xad_zh.ts -qm    $SOURCE_PATH/release/$BUILD_NAME/base/lang/xad_zh.qm
$QT_PATH/bin/lrelease  $SOURCE_PATH/gui_source/translation/xad_zh_TW.ts -qm $SOURCE_PATH/release/$BUILD_NAME/base/lang/xad_zh_TW.qm
$QT_PATH/bin/lrelease  $SOURCE_PATH/gui_source/translation/xad_ko.ts -qm    $SOURCE_PATH/release/$BUILD_NAME/base/lang/xad_ko.qm

echo "#!/bin/sh" >> release/$BUILD_NAME/xad.sh
echo "CWD=\$(dirname \$0)" >> release/$BUILD_NAME/xad.sh
echo "export LD_LIBRARY_PATH=\"\$CWD/base:\$LD_LIBRARY_PATH\"" >> release/$BUILD_NAME/xad.sh
echo "\$CWD/base/xad \$*" >> release/$BUILD_NAME/xad.sh

echo "#!/bin/sh" >> release/$BUILD_NAME/xadc.sh
echo "CWD=\$(dirname \$0)" >> release/$BUILD_NAME/xadc.sh
echo "export LD_LIBRARY_PATH=\"\$CWD/base:\$LD_LIBRARY_PATH\"" >> release/$BUILD_NAME/xadc.sh
echo "\$CWD/base/xadc \$*" >> release/$BUILD_NAME/xadc.sh

chmod +x release/$BUILD_NAME/xad.sh
chmod +x release/$BUILD_NAME/xadc.sh

rm -rf $SOURCE_PATH/release/${BUILD_NAME}_${RELEASE_VERSION}.tar.gz
rm -rf $SOURCE_PATH/release/${BUILD_NAME}_${RELEASE_VERSION}.tar

cd release

tar -cvf ${BUILD_NAME}_${RELEASE_VERSION}.tar $BUILD_NAME
gzip --best ${BUILD_NAME}_${RELEASE_VERSION}.tar

cd ..

rm -rf release/$BUILD_NAME
