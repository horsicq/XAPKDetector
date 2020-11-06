// Copyright (c) 2018-2019 hors<horsicq@gmail.com>
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
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "staticscanitemmodel.h"
#include "../global.h"

void ScanFiles(QList<QString> *pListArgs,SpecAbstract::SCAN_OPTIONS *pScanOptions)
{
    QList<QString> listFileNames;

    for(int i=0;i<pListArgs->count();i++)
    {
        QString sFileName=pListArgs->at(i);

        if(QFileInfo::exists(sFileName))
        {
            XBinary::findFiles(sFileName,&listFileNames);
        }
        else
        {
            printf("Cannot find: %s\n",sFileName.toLatin1().data());
        }
    }

    bool bShowFileName=listFileNames.count()>1;

    for(int i=0;i<listFileNames.count();i++)
    {
        QString sFileName=listFileNames.at(i);

        if(bShowFileName)
        {
            printf("%s:\n",sFileName.toLatin1().data());
        }

        SpecAbstract::SCAN_RESULT scanResult=StaticScan::processFile(sFileName,pScanOptions);
        StaticScanItemModel model(&scanResult.listRecords);

        printf("%s\n",model.toString(pScanOptions).toLatin1().data());
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(X_ORGANIZATIONNAME);
    QCoreApplication::setOrganizationDomain(X_ORGANIZATIONDOMAIN);
    QCoreApplication::setApplicationName(X_APPLICATIONNAME);
    QCoreApplication::setApplicationVersion(X_APPLICATIONVERSION);

    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    QString sDescription;
    sDescription.append(QString("%1 v%2\n").arg(X_APPLICATIONNAME).arg(X_APPLICATIONVERSION));
    sDescription.append(QString("%1\n").arg("Copyright(C) 2020 hors<horsicq@gmail.com> Web: http://ntinfo.biz"));
    parser.setApplicationDescription(sDescription);
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("file","The file to open.");

    QCommandLineOption clRecursiveScan(QStringList()<<"r"<<"recursivescan","Recursive scan.");
    QCommandLineOption clDeepScan(QStringList()<<"d"<<"deepscan","Deep scan.");
    QCommandLineOption clHeuristicScan(QStringList()<<"e"<<"heuristicscan","Heuristic scan.");
    QCommandLineOption clResultAsXml(QStringList()<<"x"<<"xml","Result as XML.");
    QCommandLineOption clResultAsJson(QStringList()<<"j"<<"json","Result as JSON.");

    parser.addOption(clRecursiveScan);
    parser.addOption(clDeepScan);
    parser.addOption(clHeuristicScan);
    parser.addOption(clResultAsXml);
    parser.addOption(clResultAsJson);

    parser.process(app);

    QList<QString> listArgs=parser.positionalArguments();

    SpecAbstract::SCAN_OPTIONS scanOptions={0};

    scanOptions.bRecursiveScan=parser.isSet(clRecursiveScan);
    scanOptions.bDeepScan=parser.isSet(clDeepScan);
    scanOptions.bHeuristicScan=parser.isSet(clHeuristicScan);
    scanOptions.bResultAsXML=parser.isSet(clResultAsXml);
    scanOptions.bResultAsJSON=parser.isSet(clResultAsJson);

    if(listArgs.count())
    {
        ScanFiles(&listArgs,&scanOptions);
    }
    else
    {
        parser.showHelp();
        Q_UNREACHABLE();
    }

    return 0;
}
