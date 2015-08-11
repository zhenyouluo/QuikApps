/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the documentation of Qt. It was originally
** published as part of Qt Quarterly.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights.  These rights are described in the Nokia Qt LGPL
** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QTextDocument>
#include <QtNetwork>
#include <iostream>
using namespace std;
#include "localreply.h"
#include "localapp.h"
#include "qfileerror.h"
#include "global.h"
#include "UiMainWindow.h"

extern class Ui_MainWindow *globalUi;

LocalReply::LocalReply(const QUrl &url, const QNetworkRequest &request, QByteArray &postQueryData, QByteArray &contentType, bool isGetQuery = true)
    : QNetworkReply()
{
    ERR<<"INFO: LocalReply::LocalReply(): LOCAL File = "<<url.toDisplayString()<<endl;
    ERR<<"INFO: LocalReply::LocalReply(): LOCAL Query Data = "<<url.query()<<endl;
    scriptOutput = 0;
    timer  = new QTimer(this);
    if ( contentType.length() > 0 ) {
        recvContentType   = contentType;
        isMultiPart = true;
        ERR<<"INFO: LocalReply::LocalReply(): Post Data is MultiPart"<<endl;
    }
    else {
        isMultiPart = false;
        if ( isGetQuery ){
            ERR<<"INFO: LocalReply::LocalReply(): Get Query"<<endl;
        } else {
            ERR<<"INFO: LocalReply::LocalReply(): Post Data is not MultiPart"<<endl;
        }
    }
    QUrl tmpUrl = url;
    QString appName  = LocalApp::readAppName(url);
    ERR<<"INFO: LocalReply::LocalReply(): App: "<<appName<<endl;
    LocalApp *localApp = LocalApp::getApp(appName);
    if(!localApp){
        ERR<<"DBUG: LocalReply::LocalReply(): Creating new local app "<<endl;
        localApp = new LocalApp(0,appName);
        LocalApp::addApp(appName, localApp);
    } else {
        ERR<<"DBUG: LocalReply::LocalReply(): Using existing app "<<endl;
    }
    localApp->getUrl(url, tmpUrl);
    setUrl(tmpUrl);
    setRequest(request);
    delta = 0;
    isScriptFile    = false;
    isForbiddenFile = false;

#ifndef USE_QT5
    scriptName   = tmpUrl.encodedPath();//tmpUrl.toString(FULLPATH);
    ERR<<"DBUG: LocalReply::LocalReply(): Accessing Local file : "<<tmpUrl.encodedPath()<<endl;
#else
    scriptName   = tmpUrl.path();//tmpUrl.toDisplayString(QUrl::FullyDecoded);
    ERR<<"DBUG: LocalReply::LocalReply(): Accessing Local file : "<<tmpUrl.path()<<endl;
#endif

    ERR<<"DBUG: LocalReply::LocalReply(): Local file : "<<scriptName<<endl;
    isScriptFile    = localApp->isScript(scriptName);
    if (isScriptFile) {
        isForbiddenFile = false;
    } else {
        isForbiddenFile = localApp->isForbidden(scriptName);
    }

    postData     = postQueryData;
    isGet        = isGetQuery;
    soScript     = localApp->getScript(scriptName);

    if (!isScriptFile){
        if ( !isForbiddenFile ){
            scriptOutput  = new QFile( scriptName);
#ifndef USE_QT5
            if(! scriptOutput->open(QIODevice::ReadOnly) ){
#else
            if(! scriptOutput->open(QFile::ReadOnly) ){
#endif
                    ERR<<"INFO: LocalReply::LocalReply(): Unable to open file "<<scriptOutput->fileName()<<endl;
                    ERR<<"INFO: LocalReply::LocalReply(): Exists ? "<<scriptOutput->exists()<<endl;
            }
            ERR<<"INFO: LocalReply::LocalReply(): Reading from: "<<scriptOutput->fileName()<<endl;
        }
    }


    connect(timer, SIGNAL(timeout()), this, SLOT(processTimeout()));

    timer->setInterval ( 1 );
    timer->setSingleShot (true );
    timer->start();
}



LocalReply::~LocalReply()
{
    ERR<<"INFO: LocalReply::~LocalReply(): Cleaning up ... "<<endl;//script->fileName()<<endl;
    delete timer;
    if( scriptOutput ){
        scriptOutput->close();
        delete scriptOutput;
    }
}


void LocalReply::abort()
{
    ERR<<"INFO: LocalReply::abort(): Abort requested"<<endl;
}

QString LocalReply::getScriptOutputName(){
    ERR<<"INFO: LocalReply::getScriptOutputName(): "<<scriptOutput->fileName()<<endl;
    return scriptOutput->fileName();
}

QString LocalReply::getScriptContentTypeFileName(){
    ERR<<"INFO: LocalReply::getScriptContentTypeFileName(): "<<scriptOutput->fileName()<<".type"<<endl;
    return QString(scriptOutput->fileName()+QString(".type"));
}

qint64 LocalReply::getScriptOutputSize(){
    ERR<<"INFO: LocalReply::getScriptOutputSize(): "<<scriptOutput->size()<<endl;
    return scriptOutput->size();
}

bool LocalReply::isScript(QString &fext){
    ERR<<"INFO: LocalReply::isScript(): Extension Type: "<<fext<<endl;
    if ( fext == QString("py") )
        return true;
    return false;
}

void LocalReply::getContentType(){
    if(isForbiddenFile)
        return;
    QFile *contentTypeFile = new QFile (scriptName+QString(".type"));
    ERR<<"INFO: LocalReply::getContentType(): "<<contentTypeFile->fileName()<<endl;
    ERR.flush();
#ifndef USE_QT5
    if ( ! contentTypeFile->open(QIODevice::ReadOnly) ){
#else
    if ( ! contentTypeFile->open(QFile::ReadOnly) ){
#endif
        QString fext = QFileInfo(scriptName).suffix();
        extern MapStrStr * contentType;
        MapStrStr::iterator i = contentType->find(QString(fext.data()));
        if ( i != contentType->end() ){
            ctypeInfo.append(i.value());
            ERR<<"DBUG: LocalReply::getContentType(): "<<i.value()<<endl;
        } else {
            ERR<<"DBUG: LocalReply::getContentType(): Unable to Open, setting as : text/html"<<endl;
            ctypeInfo.append("text/html");
        }
        contentTypeFile->close();
    }else {
        ctypeInfo = contentTypeFile->readAll();
        ERR<<"DBUG: LocalReply::getContentType(): "<<ctypeInfo<<endl;
    }
    delete contentTypeFile;
}

void LocalReply::processTimeout(){
    ERR<<"INFO: LocalReply::processTimeout(): timeout happened"<<endl;
    runScript();
}

void LocalReply::runScript(){
    open(ReadOnly | Unbuffered);
    getContentType();
    if ( !isScriptFile ){
        if (!isForbiddenFile ){
            ERR<<"INFO: LocalReply::runScript(): Reading data from "<<scriptOutput->fileName()<<endl;
            ERR.flush();
            content = scriptOutput->readAll();
            setHeader(QNetworkRequest::ContentTypeHeader, ctypeInfo.constData());
            setHeader(QNetworkRequest::ContentLengthHeader, QVariant(content.size()));
            setRawHeader("Cache-Control","no-cache");
            setRawHeader("Pragma","no-cache");
        } else {
            ERR<<"INFO: LocalReply::runScript(): Forbidden file sending 403 Forbidden "<<endl;
            ERR.flush();
            setError(ContentAccessDenied,"Forbidden");
            content = "<html><head><title>Forbidden file</title></head><body><h1>403 Forbidden file</h1></body></html>";
            setHeader(QNetworkRequest::ContentTypeHeader, "text/html");
            setHeader(QNetworkRequest::ContentLengthHeader, QVariant(content.size()));
            setRawHeader("Cache-Control","no-cache");
            setRawHeader("Pragma","no-cache");
        }
        emit readyRead();
        emit finished();
    } else {
        typedef void (*scriptfunction)(QUrl, QByteArray, QByteArray&, QByteArray, bool, bool);
        scriptfunction pluginFunction = (scriptfunction)soScript->resolve("pluginexecute");
        if ( pluginFunction ){
            pluginFunction(url(), postData, content, recvContentType, isGet, isMultiPart);
            //content = "<html><head><title>Not Found</title></head><body><h1>200 OK</h1></body></html>";
            threadFinished();
        } else {
            ERR<<"DBUG: LocalReply::runScript(): Not running script "<<endl;
            setError(ContentNotFoundError,"Not Found");
            content = "<html><head><title>Not Found</title></head><body><h1>404 Not Found</h1></body></html>";
            setHeader(QNetworkRequest::ContentTypeHeader, "text/html");
            setHeader(QNetworkRequest::ContentLengthHeader, QVariant(content.size()));
            setRawHeader("Cache-Control","no-cache");
            setRawHeader("Pragma","no-cache");
            emit readyRead();
            emit finished();
        }


        QUrl tmpurl = url();
#ifndef USE_QT5
        ERR<<"DBUG: LocalReply::runScript(): Executing Script: "<<tmpurl.encodedPath()<<endl;
#else
        ERR<<"DBUG: LocalReply::runScript(): Executing Script: "<<tmpurl.path()<<", query: "<<tmpurl.query()<<endl;
#endif
    }
}

void LocalReply::threadFinished(){
    ERR<<"DBUG: LocalReply::threadFinished(): Output Size: "<<content.size()<<endl;
    setHeader(QNetworkRequest::ContentTypeHeader, ctypeInfo.constData());
    setHeader(QNetworkRequest::ContentLengthHeader, QVariant(content.size()));
    //setHeader(QNetworkRequest::CacheLoadControl, QVariant(QString("no-cache")));
    setRawHeader("Cache-Control","no-cache");
    setRawHeader("Pragma","no-cache");
    emit readyRead();
    emit finished();
}


void LocalReply::threadTerminated(){
    ERR<<"DBUG: LocalReply::threadTerminated(): "<<endl;
}

qint64 LocalReply::bytesAvailable() const
{
    return content.size() - delta + QIODevice::bytesAvailable();
}

bool LocalReply::isSequential() const
{
    return true;
}

qint64 LocalReply::readData(char *data, qint64 maxSize)
{
    if (content.size() <= 0 ){
        return -1;
    }
    if (delta < content.size()) {
            qint64 number = qMin(maxSize, content.size() - delta);
            memcpy(data, content.constData() + delta, number);
            delta += number;
            return number;
        } else
            return -1;

    ERR<<"INFO: LocalReply::readData(): "<<maxSize<<", "<<delta<<endl;
}

qint64 LocalReply::writeData(char *data, qint64 maxSize)
{
    ERR<<"INFO: LocalReply::writeData(): possible post data"<<endl;
    return 0;
}

