// Copyright (c) 2018-2020 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "guimainwindow.h"
#include "ui_guimainwindow.h"

GuiMainWindow::GuiMainWindow(QWidget *pParent) :
    QMainWindow(pParent),
    ui(new Ui::GuiMainWindow)
{
    ui->setupUi(this);

    setWindowTitle(QString("%1 v%2").arg(X_APPLICATIONNAME).arg(X_APPLICATIONVERSION));

    setAcceptDrops(true);

    fwOptions={};

    ui->pushButtonClassesDex->setEnabled(false);

    xOptions.setName(X_OPTIONSFILE);

    QList<XOptions::ID> listIDs;

    listIDs.append(XOptions::ID_STYLE);
    listIDs.append(XOptions::ID_QSS);
    listIDs.append(XOptions::ID_LANG);
    listIDs.append(XOptions::ID_SCANAFTEROPEN);
    listIDs.append(XOptions::ID_STAYONTOP);
    listIDs.append(XOptions::ID_SAVELASTDIRECTORY);
    listIDs.append(XOptions::ID_LASTDIRECTORY);

    xOptions.setValueIDs(listIDs);

//    QMap<XOptions::ID,QVariant> mapDefaultValues;
//    mapDefaultValues.insert(XOptions::ID_QSS,"");

//    xOptions.setDefaultValues(mapDefaultValues);

    xOptions.load();
    adjust();

    if(QCoreApplication::arguments().count()>1)
    {
        handleFile(QCoreApplication::arguments().at(1));
    }
}

GuiMainWindow::~GuiMainWindow()
{
    xOptions.save();

    delete ui;
}

void GuiMainWindow::handleFile(QString sFileName)
{
    QFileInfo fi(sFileName);

    if(fi.isFile())
    {
        ui->lineEditFileName->setText(sFileName);
        
        ui->widgetArchive->setData(sFileName,&fwOptions);

        ui->pushButtonClassesDex->setEnabled(XArchives::isArchiveRecordPresent(sFileName,"classes.dex"));

        if(xOptions.isScanAfterOpen())
        {
            scanFile(sFileName);
        }

        xOptions.setLastDirectory(sFileName);
    }
}

void GuiMainWindow::on_pushButtonExit_clicked()
{
    this->close();
}

void GuiMainWindow::on_pushButtonOpenFile_clicked()
{
    QString sDirectory=xOptions.getLastDirectory();

    QString sFileName=QFileDialog::getOpenFileName(this,tr("Open file")+QString("..."),sDirectory,tr("All files")+QString(" (*)"));

    if(!sFileName.isEmpty())
    { 
        handleFile(sFileName);
    }
}

void GuiMainWindow::on_pushButtonScan_clicked()
{
    QString sFileName=ui->lineEditFileName->text().trimmed();

    if(sFileName!="")
    {
        scanFile(sFileName);
    }
}

void GuiMainWindow::on_pushButtonAbout_clicked()
{
    DialogAbout di(this);

    di.exec();
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
    const QMimeData *pMimeData=pEvent->mimeData();

    if(pMimeData->hasUrls())
    {
        QList<QUrl> urlList=pMimeData->urls();

        if(urlList.count())
        {
            QString sFileName=urlList.at(0).toLocalFile();

            sFileName=XBinary::convertFileName(sFileName);

            handleFile(sFileName);
        }
    }
}

void GuiMainWindow::on_pushButtonOptions_clicked()
{
    DialogOptions dialogOptions(this,&xOptions);

    dialogOptions.exec();

    adjust();
}

void GuiMainWindow::adjust()
{
    xOptions.adjustStayOnTop(this);
}

void GuiMainWindow::on_pushButtonHex_clicked()
{
    QString sFileName=ui->lineEditFileName->text().trimmed();

    if(sFileName!="")
    {
        QFile file;
        file.setFileName(sFileName);

        if(file.open(QIODevice::ReadOnly))
        {
            DialogHex dialogHex(this,&file);

            dialogHex.exec();

            file.close();
        }
    }
}

void GuiMainWindow::on_pushButtonStrings_clicked()
{
    QString sFileName=ui->lineEditFileName->text().trimmed();

    if(sFileName!="")
    {
        QFile file;
        file.setFileName(sFileName);

        if(file.open(QIODevice::ReadOnly))
        {
            DialogSearchStrings dialogSearchStrings(this,&file,nullptr,true);

            dialogSearchStrings.exec();

            file.close();
        }
    }
}

void GuiMainWindow::on_pushButtonHash_clicked()
{
    QString sFileName=ui->lineEditFileName->text().trimmed();

    if(sFileName!="")
    {
        QFile file;
        file.setFileName(sFileName);

        if(file.open(QIODevice::ReadOnly))
        {
            DialogHash dialogHash(this,&file);

            dialogHash.exec();

            file.close();
        }
    }
}

void GuiMainWindow::on_pushButtonEntropy_clicked()
{
    QString sFileName=ui->lineEditFileName->text().trimmed();

    if(sFileName!="")
    {
        QFile file;
        file.setFileName(sFileName);

        if(file.open(QIODevice::ReadOnly))
        {
            DialogEntropy dialogEntropy(this,&file);

            dialogEntropy.exec();

            file.close();
        }
    }
}

void GuiMainWindow::scanFile(QString sFileName)
{
    QFile file;
    file.setFileName(sFileName);

    if(file.open(QIODevice::ReadOnly))
    {
        DialogStaticScan dialogStaticScan(this,&file,true);

        dialogStaticScan.exec();

        file.close();
    }
}

void GuiMainWindow::on_pushButtonClassesDex_clicked()
{
    QString sFileName=ui->lineEditFileName->text().trimmed();

    if(sFileName!="")
    {
        QTemporaryFile fileTemp;

        if(fileTemp.open())
        {
            QString sTempFileName=fileTemp.fileName();

            if(XArchives::decompressToFile(sFileName,"classes.dex",sTempFileName))
            {
                QFile file;
                file.setFileName(sTempFileName);

                if(file.open(QIODevice::ReadOnly))
                {
                    fwOptions.nStartType=SDEX::TYPE_HEADER;
                    fwOptions.sTitle="classes.dex";

                    DialogDEX dialogDEX(this);

                    dialogDEX.setData(&file,&fwOptions);

                    dialogDEX.exec();

                    file.close();
                }
            }
        }
    }
}
