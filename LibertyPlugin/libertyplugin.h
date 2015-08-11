#ifndef LIBERTYPLUGIN_H
#define LIBERTYPLUGIN_H

#include "libertyplugin_global.h"
#include <QByteArray>
#include <QString>
#include <QMap>
#include <QList>
#include <QPair>
#include <QUrl>
#include <QUrlQuery>

extern "C" void pluginexecute( QUrl url, QByteArray inData, QByteArray &outData, QByteArray contentType, bool isGet, bool isMultipart);


#endif // LIBERTYPLUGIN_H
