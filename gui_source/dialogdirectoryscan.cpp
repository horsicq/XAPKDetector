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
#include "dialogdirectoryscan.h"
#include "ui_dialogdirectoryscan.h"

DialogDirectoryScan::DialogDirectoryScan(QWidget *parent, NFD::OPTIONS *pOptions,QString sDirName) :
    QDialog(parent),
    ui(new Ui::DialogDirectoryScan)
{
    ui->setupUi(this);

    this->pOptions=pOptions;

    setWindowFlags(windowFlags()|Qt::WindowMinMaxButtonsHint);

//    Qt::WindowTitleHint

    connect(this,SIGNAL(resultSignal(QString)),this,SLOT(appendResult(QString)));

    ui->checkBoxScanSubdirectories->setChecked(true);

    if(pOptions->bSaveLastDirectory&&QDir().exists(pOptions->sLastDirectory))
    {
        ui->lineEditDirectoryName->setText(pOptions->sLastDirectory);
    }

    if(sDirName!="")
    {
        ui->lineEditDirectoryName->setText(sDirName);
        if(pOptions->bScanAfterOpen)
        {
            scanDirectory(sDirName);
        }
    }
}

DialogDirectoryScan::~DialogDirectoryScan()
{
    delete ui;
}

void DialogDirectoryScan::on_pushButtonOpenDirectory_clicked()
{
    QString sInitDirectory=ui->lineEditDirectoryName->text();

    QString sDirectoryName=QFileDialog::getExistingDirectory(this,tr("Open directory")+QString("..."),sInitDirectory,QFileDialog::ShowDirsOnly);

    if(!sDirectoryName.isEmpty())
    {
        ui->lineEditDirectoryName->setText(sDirectoryName);
        if(pOptions->bScanAfterOpen)
        {
            scanDirectory(sDirectoryName);
        }
    }
}

void DialogDirectoryScan::on_pushButtonScan_clicked()
{
    QString sDirectoryName=ui->lineEditDirectoryName->text().trimmed();

    scanDirectory(sDirectoryName);
}

void DialogDirectoryScan::scanDirectory(QString sDirectoryName)
{
    if(sDirectoryName!="")
    {
        ui->textBrowserResult->clear();

        SpecAbstract::SCAN_OPTIONS options={0};
        options.bRecursiveScan=ui->checkBoxRecursiveScan->isChecked();
        options.bDeepScan=ui->checkBoxDeepScan->isChecked();
        options.bHeuristicScan=ui->checkBoxHeuristicScan->isChecked();
        options.bSubdirectories=ui->checkBoxScanSubdirectories->isChecked();
        // TODO Filter
        // |flags|x all|

        DialogStaticScan ds(this);
        connect(&ds, SIGNAL(scanResult(SpecAbstract::SCAN_RESULT)),this,SLOT(scanResult(SpecAbstract::SCAN_RESULT)),Qt::DirectConnection);
        ds.setData(sDirectoryName,&options);
        ds.exec();

        if(pOptions->bSaveLastDirectory)
        {
            QDir dir(sDirectoryName);
            if(dir.exists())
            {
                pOptions->sLastDirectory=dir.absolutePath();
            }
        }
    }
}

void DialogDirectoryScan::scanResult(SpecAbstract::SCAN_RESULT scanResult)
{
    QString sResult=QString("%1 %2 %3").arg(scanResult.sFileName).arg(scanResult.nScanTime).arg(tr("msec"));
    sResult+="\r\n";
    StaticScanItemModel model(&scanResult.listRecords);
    SpecAbstract::SCAN_OPTIONS scanOptions={};
    sResult+=model.toString(&scanOptions).toLatin1().data();

    emit resultSignal(sResult);
}

void DialogDirectoryScan::appendResult(QString sResult)
{
    ui->textBrowserResult->append(sResult);
}

void DialogDirectoryScan::on_pushButtonOK_clicked()
{
    this->close();
}

void DialogDirectoryScan::on_pushButtonClear_clicked()
{
    ui->textBrowserResult->clear();
}

void DialogDirectoryScan::on_pushButtonSave_clicked()
{
    QString sFilter;
    sFilter+=QString("%1 (*.txt)").arg(tr("Text documents"));
    QString sSaveFileName=pOptions->sLastDirectory+QDir::separator()+"result";
    QString sFileName=QFileDialog::getSaveFileName(this,tr("Save result"),sSaveFileName,sFilter);

    if(!sFileName.isEmpty())
    {
        QFile file;
        file.setFileName(sFileName);

        if(file.open(QIODevice::ReadWrite))
        {
            QString sText=ui->textBrowserResult->toPlainText();
            file.write(sText.toLatin1().data());

            file.close();
        }
    }
}
