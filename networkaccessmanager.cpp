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

#include <QtNetwork>
#include <QList>
#include "networkaccessmanager.h"
#include "localreply.h"
#include "qfileerror.h"

NetworkAccessManager::NetworkAccessManager(QNetworkAccessManager *manager, QObject *parent)
    : QNetworkAccessManager(parent)
{
    setCache(manager->cache());
    setCookieJar(manager->cookieJar());
    setProxy(manager->proxy());
    setProxyFactory(manager->proxyFactory());
}

QNetworkReply *NetworkAccessManager::createRequest(
    QNetworkAccessManager::Operation operation, const QNetworkRequest &request,
    QIODevice *device)
{
    if (request.url().scheme() != "local")
        return QNetworkAccessManager::createRequest(operation, request, device);

    if (operation == GetOperation ){
        // Handle ftp:// URLs separately by creating custom QNetworkReply
        // objects.
        ERR<<"DBUG: NetworkAccessManager::createRequest(): GET Operation"<<endl;
        QByteArray tmp;
        QByteArray contentType;
        ERR<<"DBUG: NetworkAccessManager::createRequest(): QUERY : "<<request.url().toDisplayString()<<endl;
        ERR<<"DBUG: NetworkAccessManager::createRequest(): QUERY DATA: "<<request.url().query()<<endl;
        LocalReply *lreply = new LocalReply(request.url(), request, tmp, contentType, true );
        return lreply;

    } else
    if(operation == PostOperation ){
        ERR<<"DBUG: NetworkAccessManager::createRequest(): POST Operation"<<endl;
        QByteArray postData = device->readAll();

        QList<QByteArray> headers = request.rawHeaderList();
        QList<QByteArray>::iterator i = headers.begin();
        QByteArray contentType;
        while( i != headers.end()){
            QByteArray tmpHeaderValue = request.rawHeader(*i);
            ERR<<"DBUG: NetworkAccessManager::createRequest(): "<<i->data()<<" : "<<tmpHeaderValue<<endl;
            if( *i == QString("Content-Type") && tmpHeaderValue.contains("multipart/form-data;") ){
                contentType = tmpHeaderValue;
                QList<QByteArray> tmpContentType = tmpHeaderValue.split('=');
                QByteArray tmpBoundary = tmpContentType[1];
                tmpBoundary.prepend("--");
                ERR<<"DBUG: NetworkAccessManager::createRequest(): Multipart Boundary = "<<tmpBoundary<<endl;
            }
            i++;
        }
        LocalReply *lreply = new LocalReply(request.url(), request, postData, contentType,false  );
        //ERR<<"DBUG: NetworkAccessManager::createRequest(): POST Data : "<<postData<<endl;
        return lreply;
    }
    else
        return QNetworkAccessManager::createRequest(operation, request, device);
}
