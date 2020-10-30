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
#ifndef GUIMAINWINDOW_H
#define GUIMAINWINDOW_H

#include "../global.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QMimeData>
#include "dialogabout.h"
#include "dialogoptions.h"
#include "archive_widget.h"
#include "xoptions.h"

namespace Ui
{
class GuiMainWindow;
}

class GuiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiMainWindow(QWidget *pParent=nullptr);
    ~GuiMainWindow() override;

private slots:
    void handleFile(QString sFileName);
    void on_pushButtonScan_clicked();
    void on_pushButtonExit_clicked();
    void on_pushButtonOpenFile_clicked();
    void on_pushButtonAbout_clicked();
    void on_pushButtonOptions_clicked();
    void adjust();
    void on_pushButtonHex_clicked();
    void on_pushButtonStrings_clicked();
    void on_pushButtonHash_clicked();
    void on_pushButtonEntropy_clicked();
    void scanFile(QString sFileName);
    void on_pushButtonClassesDex_clicked();

protected:
    void dragEnterEvent(QDragEnterEvent *pEvent) override;
    void dragMoveEvent(QDragMoveEvent *pEvent) override;
    void dropEvent(QDropEvent *pEvent) override;

private:
    Ui::GuiMainWindow *ui;
    XOptions xOptions;
    FW_DEF::OPTIONS fwOptions;
};

#endif // GUIMAINWINDOW_H
