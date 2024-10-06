/* Copyright (c) 2020-2023 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "guimainwindow.h"

#include "ui_guimainwindow.h"

GuiMainWindow::GuiMainWindow(QWidget *pParent) : QMainWindow(pParent), ui(new Ui::GuiMainWindow)
{
    ui->setupUi(this);

    setWindowTitle(XOptions::getTitle(X_APPLICATIONDISPLAYNAME, X_APPLICATIONVERSION));

    setAcceptDrops(true);

    g_fwOptions = {};

    ui->pushButtonDEX->setEnabled(false);
    ui->pushButtonELF->setEnabled(false);
    ui->pushButtonManifestMF->setEnabled(false);
    ui->pushButtonAndroidManifest->setEnabled(false);
    ui->pushButtonSignature->setEnabled(false);

    g_xOptions.setName(X_OPTIONSFILE);

    g_xOptions.addID(XOptions::ID_VIEW_STYLE, "Fusion");
    g_xOptions.addID(XOptions::ID_VIEW_QSS, "");
    g_xOptions.addID(XOptions::ID_VIEW_LANG, "System");
    g_xOptions.addID(XOptions::ID_VIEW_STAYONTOP, false);
    g_xOptions.addID(XOptions::ID_FILE_SAVELASTDIRECTORY, true);
    g_xOptions.addID(XOptions::ID_FILE_SAVEBACKUP, true);

#ifdef Q_OS_WIN
    g_xOptions.addID(XOptions::ID_FILE_CONTEXT, "*");
#endif

    DIEOptionsWidget::setDefaultValues(&g_xOptions);
    SearchSignaturesOptionsWidget::setDefaultValues(&g_xOptions);
    XHexViewOptionsWidget::setDefaultValues(&g_xOptions);
    XDisasmViewOptionsWidget::setDefaultValues(&g_xOptions);

    g_xOptions.load();

    g_xShortcuts.setName(X_SHORTCUTSFILE);

    g_xShortcuts.addGroup(XShortcuts::GROUPID_STRINGS);
    g_xShortcuts.addGroup(XShortcuts::GROUPID_SIGNATURES);
    g_xShortcuts.addGroup(XShortcuts::GROUPID_HEX);
    g_xShortcuts.addGroup(XShortcuts::GROUPID_DISASM);
    g_xShortcuts.addGroup(XShortcuts::GROUPID_ARCHIVE);

    g_xShortcuts.load();

    ui->widgetArchive->setGlobal(&g_xShortcuts, &g_xOptions);

    adjustWindow();

    ui->widgetArchive->setGlobal(&g_xShortcuts, &g_xOptions);

    if (QCoreApplication::arguments().count() > 1) {
        handleFile(QCoreApplication::arguments().at(1));
    }
}

GuiMainWindow::~GuiMainWindow()
{
    g_xOptions.save();
    g_xShortcuts.save();

    delete ui;
}

void GuiMainWindow::handleFile(QString sFileName)
{
    QFileInfo fi(sFileName);

    if (fi.isFile()) {
        ui->lineEditFileName->setText(sFileName);

        ui->widgetArchive->setFileName(sFileName, XBinary::FT_UNKNOWN, g_fwOptions, QSet<XBinary::FT>());

        g_listDEX = ui->widgetArchive->getRecordsByFileType(XBinary::FT_DEX);
        g_listELF = ui->widgetArchive->getRecordsByFileType(XBinary::FT_ELF);
        //        g_listAndroidXML=ui->widgetArchive->getRecordsByFileType(XBinary::FT_ANDROIDXML);

        ui->pushButtonDEX->setEnabled(g_listDEX.count());
        ui->pushButtonELF->setEnabled(g_listELF.count());
        ui->pushButtonAndroidManifest->setEnabled(XArchives::isArchiveRecordPresent(sFileName, "AndroidManifest.xml"));
        ui->pushButtonManifestMF->setEnabled(XArchives::isArchiveRecordPresent(sFileName, "META-INF/MANIFEST.MF"));
        ui->pushButtonSignature->setEnabled(XFormats::isSigned(sFileName));

        if (g_xOptions.isScanAfterOpen()) {
            scanFile(sFileName);
        }

        g_xOptions.setLastDirectory(sFileName);
    }
}

void GuiMainWindow::on_pushButtonExit_clicked()
{
    this->close();
}

void GuiMainWindow::on_pushButtonOpenFile_clicked()
{
    QString sDirectory = g_xOptions.getLastDirectory();

    QString sFileName = QFileDialog::getOpenFileName(this, tr("Open file") + QString("..."), sDirectory, tr("All files") + QString(" (*)"));

    if (!sFileName.isEmpty()) {
        handleFile(sFileName);
    }
}

void GuiMainWindow::on_pushButtonScan_clicked()
{
    QString sFileName = ui->lineEditFileName->text().trimmed();

    if (sFileName != "") {
        scanFile(sFileName);
    }
}

void GuiMainWindow::on_pushButtonAbout_clicked()
{
    DialogAbout di(this);

    di.exec();
}

void GuiMainWindow::on_pushButtonShortcuts_clicked()
{
    DialogShortcuts dialogShortcuts(this);

    dialogShortcuts.setData(&g_xShortcuts);

    dialogShortcuts.exec();

    adjustWindow();
}

void GuiMainWindow::dragEnterEvent(QDragEnterEvent *pEvent)
{
    pEvent->acceptProposedAction();
}

void GuiMainWindow::dragMoveEvent(QDragMoveEvent *pEvent)
{
    pEvent->acceptProposedAction();
}

void GuiMainWindow::dropEvent(QDropEvent *pEvent)
{
    const QMimeData *pMimeData = pEvent->mimeData();

    if (pMimeData->hasUrls()) {
        QList<QUrl> urlList = pMimeData->urls();

        if (urlList.count()) {
            QString sFileName = urlList.at(0).toLocalFile();

            sFileName = XBinary::convertFileName(sFileName);

            handleFile(sFileName);
        }
    }
}

void GuiMainWindow::on_pushButtonOptions_clicked()
{
    DialogOptions dialogOptions(this, &g_xOptions);

    dialogOptions.exec();

    adjustWindow();
}

void GuiMainWindow::adjustWindow()
{
    //    ui->widgetViewer->adjustView();

    g_xOptions.adjustStayOnTop(this);
}

void GuiMainWindow::on_pushButtonHex_clicked()
{
    QString sFileName = ui->lineEditFileName->text().trimmed();

    if (sFileName != "") {
        QFile file;
        file.setFileName(sFileName);

        if (XBinary::tryToOpen(&file)) {
            XHexViewWidget::OPTIONS options = {};

            DialogHexView dialogHex(this);
            dialogHex.setData(&file, options);
            dialogHex.setGlobal(&g_xShortcuts, &g_xOptions);

            dialogHex.exec();

            file.close();
        }
    }
}

void GuiMainWindow::on_pushButtonStrings_clicked()
{
    QString sFileName = ui->lineEditFileName->text().trimmed();

    if (sFileName != "") {
        QFile file;
        file.setFileName(sFileName);

        if (file.open(QIODevice::ReadOnly)) {
            SearchStringsWidget::OPTIONS options = {};
            options.bAnsi = true;
            options.bUnicode = true;

            DialogSearchStrings dialogSearchStrings(this);
            dialogSearchStrings.setData(&file, XBinary::FT_UNKNOWN, options, true);
            dialogSearchStrings.setGlobal(&g_xShortcuts, &g_xOptions);

            dialogSearchStrings.exec();

            file.close();
        }
    }
}

void GuiMainWindow::on_pushButtonHash_clicked()
{
    QString sFileName = ui->lineEditFileName->text().trimmed();

    if (sFileName != "") {
        QFile file;
        file.setFileName(sFileName);

        if (file.open(QIODevice::ReadOnly)) {
            DialogHash dialogHash(this);
            dialogHash.setData(&file, XBinary::FT_UNKNOWN);
            dialogHash.setGlobal(&g_xShortcuts, &g_xOptions);

            dialogHash.exec();

            file.close();
        }
    }
}

void GuiMainWindow::on_pushButtonEntropy_clicked()
{
    QString sFileName = ui->lineEditFileName->text().trimmed();

    if (sFileName != "") {
        QFile file;
        file.setFileName(sFileName);

        if (file.open(QIODevice::ReadOnly)) {
            DialogEntropy dialogEntropy(this);
            dialogEntropy.setData(&file);
            dialogEntropy.setGlobal(&g_xShortcuts, &g_xOptions);

            dialogEntropy.exec();

            file.close();
        }
    }
}

void GuiMainWindow::scanFile(QString sFileName)
{
    QFile file;
    file.setFileName(sFileName);

    if (file.open(QIODevice::ReadOnly)) {
        DialogNFDScan dialogStaticScan(this);
        dialogStaticScan.setData(&file, true, XBinary::FT_UNKNOWN);
        // dialogStaticScan.setShortcuts(&g_xShortcuts);

        dialogStaticScan.exec();

        file.close();
    }
}

void GuiMainWindow::on_pushButtonSignature_clicked()
{
    QString sFileName = ui->lineEditFileName->text().trimmed();

    if (sFileName != "") {
        XBinary::OFFSETSIZE os = XFormats::getSignOffsetSize(sFileName);

        if (os.nSize) {
            QFile file;
            file.setFileName(sFileName);

            if (XBinary::tryToOpen(&file)) {
                SubDevice sd(&file, os.nOffset, os.nSize);

                if (XBinary::tryToOpen(&sd)) {
                    XHexViewWidget::OPTIONS options = {};
                    options.sTitle = tr("Signature");
                    options.nStartAddress = os.nOffset;

                    DialogHexView dialogHex(this);
                    dialogHex.setData(&sd, options);
                    dialogHex.setGlobal(&g_xShortcuts, &g_xOptions);

                    dialogHex.exec();

                    sd.close();
                }

                file.close();
            }
        }
    }
}

void GuiMainWindow::on_pushButtonDEX_clicked()
{
    _handleList(&g_listDEX);
}

void GuiMainWindow::on_pushButtonELF_clicked()
{
    _handleList(&g_listELF);
}

void GuiMainWindow::on_pushButtonManifestMF_clicked()
{
    openFile("META-INF/MANIFEST.MF", XBinary::FT_PLAINTEXT, true);
}

void GuiMainWindow::on_pushButtonAndroidManifest_clicked()
{
    openFile("AndroidManifest.xml", XBinary::FT_ANDROIDXML, true);
}

void GuiMainWindow::openFile(QString sRecordName, XBinary::FT fileType, bool bIsVirtual)
{
    QString sFileName;

    QTemporaryFile *pFileTemp = nullptr;

    if (bIsVirtual) {
        QString _sFileName = ui->lineEditFileName->text().trimmed();

        if (_sFileName != "") {
            pFileTemp = new QTemporaryFile;

            if (pFileTemp->open()) {
                QString sTempFileName = pFileTemp->fileName();

                if (XArchives::decompressToFile(_sFileName, sRecordName, sTempFileName)) {
                    sFileName = sTempFileName;
                }
            }
        }
    } else {
        sFileName = sRecordName;
    }

    if (sFileName != "") {
        if (XBinary::checkFileType(XBinary::FT_DEX, fileType)) {
            QFile file;
            file.setFileName(sFileName);

            if (file.open(QIODevice::ReadOnly)) {
                g_fwOptions.nStartType = SDEX::TYPE_HEADER;
                g_fwOptions.sTitle = sRecordName;

                DialogDEX dialogDEX(this);
                dialogDEX.setGlobal(&g_xShortcuts, &g_xOptions);
                dialogDEX.setData(&file, g_fwOptions);

                dialogDEX.exec();

                file.close();
            }
        } else if (XBinary::checkFileType(XBinary::FT_ELF, fileType)) {
            QFile file;
            file.setFileName(sFileName);

            if (file.open(QIODevice::ReadOnly)) {
                g_fwOptions.nStartType = SELF::TYPE_Elf_Ehdr;
                g_fwOptions.sTitle = sRecordName;

                DialogELF dialogELF(this);
                dialogELF.setGlobal(&g_xShortcuts, &g_xOptions);
                dialogELF.setData(&file, g_fwOptions);

                dialogELF.exec();

                file.close();
            }
        } else if (XBinary::checkFileType(XBinary::FT_ANDROIDXML, fileType)) {
            QString sString = XAndroidBinary::getDecoded(sFileName);

            DialogTextInfo dialogTextInfo(this);
            dialogTextInfo.setTitle(sRecordName);
            dialogTextInfo.setWrap(false);

            dialogTextInfo.setText(sString);

            dialogTextInfo.exec();
        } else if (XBinary::checkFileType(XBinary::FT_PLAINTEXT, fileType)) {
            DialogTextInfo dialogTextInfo(this);
            dialogTextInfo.setTitle(sRecordName);

            dialogTextInfo.setFileName(sFileName);

            dialogTextInfo.exec();
        }
    }

    if (pFileTemp) {
        delete pFileTemp;
    }
}

void GuiMainWindow::openFile()
{
    QAction *pAction = qobject_cast<QAction *>(sender());

    if (pAction) {
        XBinary::FT fileType = (XBinary::FT)(pAction->property("FT").toInt());
        QString sFileName = pAction->property("FileName").toString();
        bool bIsVirtual = pAction->property("IsVirtual").toBool();

        openFile(sFileName, fileType, bIsVirtual);
    }
}

void GuiMainWindow::_handleList(QList<CreateViewModelProcess::RECORD> *pList)
{
    qint32 nNumberOfRecords = pList->count();

    if (nNumberOfRecords == 1) {
        openFile(pList->at(0).sRecordName, pList->at(0).ft, pList->at(0).bIsVirtual);
    } else if (nNumberOfRecords > 1) {
        QMenu contextMenu(this);

        qint32 nNumberOfActions = g_listActions.count();

        for (qint32 i = 0; i < nNumberOfActions; i++) {
            delete g_listActions.at(i);
        }

        g_listActions.clear();

        for (qint32 i = 0; i < nNumberOfRecords; i++) {
            QAction *pAction = new QAction(pList->at(i).sRecordName, this);
            pAction->setProperty("FT", pList->at(i).ft);
            pAction->setProperty("FileName", pList->at(i).sRecordName);
            pAction->setProperty("IsVirtual", pList->at(i).bIsVirtual);
            connect(pAction, SIGNAL(triggered()), this, SLOT(openFile()));

            contextMenu.addAction(pAction);

            g_listActions.append(pAction);
        }

        contextMenu.exec(QCursor::pos());
    }
}
