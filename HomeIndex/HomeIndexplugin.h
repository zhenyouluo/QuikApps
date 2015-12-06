#ifndef HomeIndexPLUGIN_H
#define HomeIndexPLUGIN_H

#include <QByteArray>
#include <QString>
#include <QMap>
#include <QList>
#include <QPair>
#include <QUrl>
#include <QUrlQuery>

extern "C" void pluginexecute( QUrl url, QByteArray inData, QByteArray &outData, QByteArray contentType, bool isGet, bool isMultipart);


#endif // HomeIndexPLUGIN_H