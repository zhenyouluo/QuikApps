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

#include "downloader.h"
#include "localview.h"
#include "networkaccessmanager.h"
#include <iostream>
using namespace std;
#include "qfileerror.h"

LocalView::LocalView(QWidget *parent):QWebView(parent)
{
    QNetworkAccessManager *oldManager = page()->networkAccessManager();
    NetworkAccessManager *newManager = new NetworkAccessManager(oldManager, this);
    page()->setNetworkAccessManager(newManager);
    current = urls.end();
    loadStatus = 0;
}

void LocalView::loadUrl(QUrl *url, bool go){
    load(*url);
}

int  LocalView::getCurrentListIndex(){
    Urls::iterator i =  urls.begin();
    int count = 0;
    while( i!= current){
        i++;
        count++;
    }
    return count;
}

void LocalView::updateWindowTitle(const QUrl &url)
{
    setWindowTitle(tr("Local Client - %1").arg(url.toString()));
}
