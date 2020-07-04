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

GuiMainWindow::GuiMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiMainWindow)
{
    ui->setupUi(this);

    setWindowTitle(QString("%1 v%2").arg(X_APPLICATIONNAME).arg(X_APPLICATIONVERSION));

    setAcceptDrops(true);

    DialogOptions::loadOptions(&nfdOptions);
    adjust();

    if(QCoreApplication::arguments().count()>1)
    {
        _scan(QCoreApplication::arguments().at(1));
    }
}

GuiMainWindow::~GuiMainWindow()
{
    DialogOptions::saveOptions(&nfdOptions);

    delete ui;
}

void GuiMainWindow::scanFile(QString sFileName)
{
    if(sFileName!="")
    {
        SpecAbstract::SCAN_RESULT scanResult={0};

        SpecAbstract::SCAN_OPTIONS options={0};

        options.bRecursiveScan=ui->checkBoxRecursiveScan->isChecked();
        options.bDeepScan=ui->checkBoxDeepScan->isChecked();
        options.bHeuristicScan=ui->checkBoxHeuristicScan->isChecked();

        DialogStaticScan ds(this);
        ds.setData(sFileName,&options,&scanResult);
        ds.exec();

        if(nfdOptions.bSaveLastDirectory)
        {
            QFileInfo fi(sFileName);
            nfdOptions.sLastDirectory=fi.absolutePath();
        }

        QString sSaveDirectory=nfdOptions.sLastDirectory+QDir::separator()+"result"; // mb TODO

        ui->widgetResult->setData(scanResult,sSaveDirectory);
    }
}

void GuiMainWindow::_scan(QString sName)
{
    QFileInfo fi(sName);

    if(fi.isFile())
    {
        ui->lineEditFileName->setText(sName);
        
        scanFile(sName);
    }
    else if(fi.isDir())
    {
        DialogDirectoryScan dds(this,&nfdOptions,sName);
        dds.exec();

        adjust();
    }
}

void GuiMainWindow::on_pushButtonExit_clicked()
{
    this->close();
}

void GuiMainWindow::on_pushButtonOpenFile_clicked()
{
    QString sDirectory;

    if( (nfdOptions.bSaveLastDirectory)&&
        (nfdOptions.sLastDirectory!="")&&
        (QDir().exists(nfdOptions.sLastDirectory)))
    {
        sDirectory=nfdOptions.sLastDirectory;
    }

    QString sFileName=QFileDialog::getOpenFileName(this,tr("Open file")+QString("..."),sDirectory,tr("All files")+QString(" (*)"));

    if(!sFileName.isEmpty())
    {
        ui->lineEditFileName->setText(sFileName);
    
        if(nfdOptions.bScanAfterOpen)
        {
            _scan(sFileName);
        }
    }
}

void GuiMainWindow::on_pushButtonScan_clicked()
{
    QString sFileName=ui->lineEditFileName->text().trimmed();

    _scan(sFileName);
}

void GuiMainWindow::on_pushButtonAbout_clicked()
{
    DialogAbout di(this);

    di.exec();
}

void GuiMainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void GuiMainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void GuiMainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData=event->mimeData();

    if(mimeData->hasUrls())
    {
        QList<QUrl> urlList=mimeData->urls();

        if(urlList.count())
        {
            QString sFileName=urlList.at(0).toLocalFile();

            sFileName=XBinary::convertFileName(sFileName);

            if(nfdOptions.bScanAfterOpen)
            {
                _scan(sFileName);
            }
        }
    }
}

void GuiMainWindow::on_pushButtonOptions_clicked()
{
    DialogOptions dialogOptions(this,&nfdOptions);

    dialogOptions.exec();

    adjust();
}

void GuiMainWindow::adjust()
{
    Qt::WindowFlags wf=windowFlags();

    if(nfdOptions.bStayOnTop)
    {
        wf|=Qt::WindowStaysOnTopHint;
    }
    else
    {
        wf&=~(Qt::WindowStaysOnTopHint);
    }
    setWindowFlags(wf);

    ui->checkBoxDeepScan->setChecked(nfdOptions.bDeepScan);
    ui->checkBoxRecursiveScan->setChecked(nfdOptions.bRecursiveScan);
    ui->checkBoxHeuristicScan->setChecked(nfdOptions.bHeristicScan);

    show();
}

void GuiMainWindow::on_pushButtonDirectoryScan_clicked()
{
    DialogDirectoryScan dds(this,&nfdOptions,"");

    dds.exec();

    adjust();
}
