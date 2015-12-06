#include "HomeIndexplugin.h"
#include <iostream>
#include <QDir>
using namespace std;

typedef QList< QPair< QString,QString > > QQueryItems;
typedef QMap<QString, QString> QMapStrStr;

QMapStrStr* parseQuery( QUrl url, QByteArray inData, bool isGet, bool isMultiPart){
    if ( isMultiPart ){
        cerr<<"WARN: HomeIndexplugin: parseQuery(): No support for multipart as yet "<<endl;
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
    cerr<<"DBUG: HomeIndexplugin: pluginexecute(): url="<<url.toDisplayString().toStdString()<<", inData="<<inData.length()<<"bytes, contentType="<<QString(contentType).toStdString()<<", isGet?"<<isGet<<", isMultiPart?"<<isMultipart<<endl;
    outData = "<html><head><title>Home List of all apps</title></head><body><h1>";
    outData +="List of all apps</h1>";
    QDir *homeDir = new QDir(QDir::homePath()+QString("/Apps"));
    QStringList dirList = homeDir->entryList(QDir::AllDirs,QDir::Name);
    outData +="<table>";
    for ( int i = 2; i < dirList.length(); i++ ){
            if( QFile::exists(QDir::homePath()+QString("/Apps/")+dirList[i]+QString("/appimage32.png")) ) {
                outData+= "<tr><td><img src=\"local:"+dirList[i]+"/appimage32.png\"><a href=\"local:"+dirList[i]+"\">"+ dirList[i] +"</a></td></tr>";
            } else {
                outData+= "<tr><td><img src=\"local:defaultappimage32.png\"><a href=\"local:"+dirList[i]+"\">"+ dirList[i] +"</a></td></tr>";
            }
    }
    outData +="</table>";
    /*QMapStrStr *mapQuery = parseQuery(url,inData, isGet, isMultipart );
    if( mapQuery ){
        outData +="<table>";
        QMapStrStr::iterator itr = mapQuery->begin();
        while( itr != mapQuery->end() ){
            cerr<<"DBUG: HomeIndexplugin: pluginexecute():"<< QString(itr.key()).toStdString()<<" : "<<QString(itr.value()).toStdString()<<endl;
            outData += "<tr><td>"+itr.key()+"</td>";
            outData += "<td>"+itr.value()+"</td></tr>";
            itr++;
        }
        outData += "</table>";
        delete mapQuery;
    } else {
        outData += "<h2>Multipart not supported as of now !!!</h2>";
    }*/
    outData += "</body></html>";
    delete homeDir;
}
