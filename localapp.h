#ifndef LOCALAPP_H
#define LOCALAPP_H

#include <QObject>
#include <QUrl>
#include <QFile>
#include <QMutex>
#include <QStringList>
#include <QDir>
#include <QLibrary>
#include <QMap>

class LocalApp;

typedef QMap<QString, LocalApp*>  MapNameToApp;
typedef QMap<QString, QLibrary*>  MapScriptToSo;

class LocalApp : public QObject
{
    Q_OBJECT

private:
    unsigned int   referenceCount;
    QString        suffixFilter;
    QString        appName;
    MapScriptToSo  mapScriptToSo;

    void readSuffixFilter();
    void readLibraryLoadConfig();
    static  MapNameToApp mapNameToApp;
    static  QMutex       mapMutex;

public:
    explicit LocalApp(QObject *parent = 0, QString AppName = "home" );
    ~LocalApp();

    bool isScript(QString file);
    bool isForbidden(QString file);
    QLibrary *getScript(QString file);

    void decReferenceCount ();
    void incReferenceCount ();

    void    getUrl( QUrl oldUrl, QUrl &newUrl );
    static QString readAppName( QUrl filename );

    static LocalApp * getApp(QString);
    static void       addApp(QString, LocalApp *);
    static void       delApp(QString);

signals:

public slots:

};

#endif // LOCALAPP_H
