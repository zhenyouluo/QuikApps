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

#include <QFileDialog>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "downloader.h"

Downloader::Downloader(QWidget *parentWidget, QNetworkAccessManager *manager)
    : QObject(parentWidget), manager(manager), parentWidget(parentWidget)
{
}

QString Downloader::chooseSaveFile(const QUrl &url)
{
    QString fileName = url.path().split("/").last();
    if (!path.isEmpty())
        fileName = QDir(path).filePath(fileName);

    return QFileDialog::getSaveFileName(parentWidget, tr("Save File"), fileName);
}

void Downloader::startDownload(const QNetworkRequest &request)
{
    downloads[request.url().toString()] = chooseSaveFile(request.url());

    QNetworkReply *reply = manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(finishDownload()));
}

void Downloader::saveFile(QNetworkReply *reply)
{
    QString newPath = downloads[reply->url().toString()];

    if (newPath.isEmpty())
        newPath = chooseSaveFile(reply->url());

    if (!newPath.isEmpty()) {
        QFile file(newPath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
            path = QDir(newPath).dirName();
            QMessageBox::information(parentWidget, tr("Download Completed"),
                                     tr("Saved '%1'.").arg(newPath));
        } else
            QMessageBox::warning(parentWidget, tr("Download Failed"),
                                 tr("Failed to save the file."));
    }
}

void Downloader::finishDownload()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
    saveFile(reply);
    //downloads.remove(reply->url().toString());
    reply->deleteLater();
}
