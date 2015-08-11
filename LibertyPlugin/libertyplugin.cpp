#include "libertyplugin.h"
#include <iostream>
using namespace std;

typedef QList< QPair< QString,QString > > QQueryItems;
typedef QMap<QString, QString> QMapStrStr;

QMapStrStr* parseQuery( QUrl url, QByteArray inData, bool isGet, bool isMultiPart){
    if ( isMultiPart ){
        cerr<<"WARN: libertyplugin: parseQuery(): No support for multipart as yet "<<endl;
        return 0;
    } else {
        QUrlQuery  *urlQuery = 0;
        QMapStrStr *mapQuery = new QMapStrStr();
        if ( isGet ){
            urlQuery = new QUrlQuery(url.query());
        } else {
            urlQuery = new QUrlQuery(QString(inData).replace("+", " "));
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


extern "C"  void pluginexecute(QUrl url, QByteArray inData, QByteArray &outData, QByteArray contentType, bool isGet, bool isMultipart){
    cerr<<"DBUG: libertyplugin: pluginexecute(): url="<<url.toDisplayString().toStdString()<<", inData="<<inData.length()<<"bytes, contentType="<<QString(contentType).toStdString()<<", isGet?"<<isGet<<", isMultiPart?"<<isMultipart<<endl;
    outData = "<html><head><title>Liberty Plugin Found</title></head><body><h1>";
    outData +="200 OK from Liberty Test plugin</h1>";
    QMapStrStr *mapQuery = parseQuery(url,inData, isGet, isMultipart );
    if( mapQuery ){
        outData +="<table>";
        QMapStrStr::iterator itr = mapQuery->begin();
        while( itr != mapQuery->end() ){
            cerr<<"DBUG: libertyplugin: pluginexecute():"<< QString(itr.key()).toStdString()<<" : "<<QString(itr.value()).toStdString()<<endl;
            outData += "<tr><td>"+itr.key()+"</td>";
            outData += "<td>"+itr.value()+"</td></tr>";
            itr++;
        }
        outData += "</table>";
        delete mapQuery;
    } else {
        outData += "<h2>Multipart not supported as of now !!!</h2>";
    }
    outData += "</body></html>";
}

