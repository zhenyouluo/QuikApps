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

#ifndef LocalReply_H
#define LocalReply_H

#include <QNetworkReply>
#include <QStringList>
#include <QTimer>
#include <QLibrary>
#include <QMap>
#include "localapp.h"
#include "mimetypes.h"

class QFtp;



class LocalReply : public QNetworkReply
{
    Q_OBJECT

public:
    LocalReply(const QUrl &url, const QNetworkRequest &request, QByteArray &postData, QByteArray &bHeader, bool isGetQuery);
    ~LocalReply();
    virtual bool    isScript(QString &);

    void   abort();
    bool   isSequential() const;
    void   runScript();
    qint64 bytesAvailable() const;

protected:
    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(char * , qint64 );

private slots:
    void processTimeout();
    void threadFinished();
    void threadTerminated();

private:

    void getContentType();

    LocalApp   *localApp;
    QLibrary   *soScript;
    QString     scriptName;
    QFile      *scriptOutput;
    QByteArray  content;
    QByteArray  ctypeInfo;
    QByteArray  postData;
    QByteArray  recvContentType;
    QStringList units;
    QTimer     *timer;

    bool        isMultiPart;
    bool        isGet;
    bool        isScriptFile;
    bool        isForbiddenFile;

    mutable qint64 delta;

public:
    QString getScriptOutputName();
    QString getScriptContentTypeFileName();
    qint64  getScriptOutputSize();
};    

#endif
