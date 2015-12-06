#!/bin/bash


echo "Creating plugin $1"

mkdir $1

printf "#ifndef %sPLUGIN_H
#define %sPLUGIN_H

#include <QByteArray>
#include <QString>
#include <QMap>
#include <QList>
#include <QPair>
#include <QUrl>
#include <QUrlQuery>

extern \"C\" void pluginexecute( QUrl url, QByteArray inData, QByteArray &outData, QByteArray contentType, bool isGet, bool isMultipart);


#endif // %sPLUGIN_H" $1 $1 $1 > $1/$1plugin.h


printf "QT       += network sql script xml

QT       -= gui

TARGET = %sPlugin
TEMPLATE = lib

DEFINES += %sPLUGIN_LIBRARY

SOURCES += %splugin.cpp

HEADERS += %splugin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

" $1 $1 $1 $1 > $1/$1.pro


printf "#include \"%splugin.h\"
#include <iostream>
using namespace std;

typedef QList< QPair< QString,QString > > QQueryItems;
typedef QMap<QString, QString> QMapStrStr;

QMapStrStr* parseQuery( QUrl url, QByteArray inData, bool isGet, bool isMultiPart){
    if ( isMultiPart ){
        cerr<<\"WARN: %splugin: parseQuery(): No support for multipart as yet \"<<endl;
        return 0;
    } else {
        QUrlQuery  *urlQuery = 0;
        QMapStrStr *mapQuery = new QMapStrStr();
        if ( isGet ){
            urlQuery = new QUrlQuery(url.query());
        } else {
            urlQuery = new QUrlQuery(QString(inData).replace(\"+\", \" \"));
        }
        QQueryItems qQueryItems = urlQuery->queryItems(QUrl::FullyDecoded);
        QQueryItems::iterator i = qQueryItems.begin();
        while( i != qQueryItems.end() ){
            (*mapQuery)[i->first]= i->second;
            i++;
        }
        delete urlQuery;
        return mapQuery;
    }
}

" $1 $1 > $1/$1plugin.cpp

printf "

extern \"C\"  void pluginexecute(QUrl url, QByteArray inData, QByteArray &outData, QByteArray contentType, bool isGet, bool isMultipart){
    cerr<<\"DBUG: %splugin: pluginexecute(): url=\"<<url.toDisplayString().toStdString()<<\", inData=\"<<inData.length()<<\"bytes, contentType=\"<<QString(contentType).toStdString()<<\", isGet?\"<<isGet<<\", isMultiPart?\"<<isMultipart<<endl;
    outData = \"<html><head><title>%s Plugin Found</title></head><body><h1>\";
    outData +=\"200 OK from %s plugin</h1>\";
    QMapStrStr *mapQuery = parseQuery(url,inData, isGet, isMultipart );
    if( mapQuery ){
        outData +=\"<table>\";
        QMapStrStr::iterator itr = mapQuery->begin();
        while( itr != mapQuery->end() ){
            cerr<<\"DBUG: %splugin: pluginexecute():\"<< QString(itr.key()).toStdString()<<\" : \"<<QString(itr.value()).toStdString()<<endl;
            outData += \"<tr><td>\"+itr.key()+\"</td>\";
            outData += \"<td>\"+itr.value()+\"</td></tr>\";
            itr++;
        }
        outData += \"</table>\";
        delete mapQuery;
    } else {
        outData += \"<h2>Multipart not supported as of now !!!</h2>\";
    }
    outData += \"</body></html>\";
}
" $1 $1 $1 $1>> $1/$1plugin.cpp


