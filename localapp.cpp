#include "localapp.h"
#include "global.h"
#include "qfileerror.h"

MapNameToApp LocalApp::mapNameToApp;
QMutex       LocalApp::mapMutex;

LocalApp::LocalApp(QObject *parent, QString AppName) :
    QObject(parent),appName(AppName),referenceCount(0),suffixFilter(".type:.suffixfilter:.cfg:")
{
    readSuffixFilter();
    readLibraryLoadConfig();
}

LocalApp::~LocalApp(){

}

void LocalApp::readSuffixFilter(){
    QFile *suffixFilterFile = 0;
    if ( appName == "home")
        suffixFilterFile = new QFile (home+"/"+QString("home.suffixfilter"));
    else
        suffixFilterFile = new QFile (home+"/"+ appName + "/"+ appName + QString(".suffixfilter"));
    ERR<<"INFO: LocalApp::readSuffixFilter(): "<<suffixFilterFile->fileName()<<endl;
#ifndef USE_QT5
    if ( ! suffixFilterFile->open(QIODevice::ReadOnly) ){
#else
    if ( ! suffixFilterFile->open(QFile::ReadOnly) ){
#endif
        ERR<<"WARN: LocalApp::readSuffixFilter(): Unable to read : "<<suffixFilterFile->fileName()<<endl;
        suffixFilterFile->close();

    }else {
        suffixFilter += suffixFilterFile->readAll();
        suffixFilterFile->close();
    }

    //TODO: convert suffix filter to map of string
    ERR<<"DBUG: LocalApp::readSuffixFilter(): "<<suffixFilter<<endl;
    delete suffixFilterFile;
}

void LocalApp::readLibraryLoadConfig(){
    QFile *llConfigFile = 0;
    if ( appName == "home")
        llConfigFile = new QFile (home+"/"+QString("home.cfg"));
    else
        llConfigFile = new QFile (home+"/"+ appName + "/"+ appName + QString(".cfg"));
#ifndef USE_QT5
    if ( ! llConfigFile->open(QIODevice::ReadOnly) ){
#else
    if ( ! llConfigFile->open(QFile::ReadOnly) ){
#endif
        ERR<<"DBUG: LocalApp::readLibraryLoadConfig(): Unable to open file :"<<llConfigFile->fileName()<<endl;
    } else {
        QByteArray libConfig;
        while ( (libConfig = llConfigFile->readLine() ).length() > 0 ){
            /*
             * Read the config file
             * <scriptname>:<libraryname>
             */
            QString line(libConfig);
            if( line.split(":").length() > 1) {
                QString script = line.split(":")[0];
                QString soFile = line.split(":")[1];
#ifndef WINDOWS
                soFile.replace(QString("\n"), QString(""));
                soFile += QString(".so");
                //soFile.remove(soFile.length()-1,1);
#else
                soFile.replace(QString("\r\n"), QString(""));
                soFile += QString(".dll");
                //soFile.remove(soFile.length()-2,2);
#endif
                if( appName == "home"){
                    QLibrary *lib = new QLibrary( home + "/" + soFile );
                    lib->setLoadHints(QLibrary::ResolveAllSymbolsHint);
                    lib->load();
                    ERR<<"ERRR: LocalApp::readLibraryLoadConfig(): "<< script<<" -> "<<lib->fileName()<<": Loaded ? "<<lib->isLoaded()<<endl;
                    mapScriptToSo[script] = lib;

                } else {
                    QLibrary *lib = new QLibrary( home + "/" + appName + "/" + soFile, this );
                    lib->setLoadHints(QLibrary::ResolveAllSymbolsHint);
                    lib->load();
                    ERR<<"ERRR: LocalApp::readLibraryLoadConfig(): "<<script<<" -> "<<lib->fileName()<<": Loaded ? "<<lib->isLoaded()<<endl;
                    mapScriptToSo[script] = lib;
                }
            }
        }
    }

    delete llConfigFile;
}


QString LocalApp::readAppName( QUrl url ){
    QString app("");
#ifndef USE_QT5
    ERR<<"INFO: LocalApp::readAppName(): Encoded Path: "<<url.encodedPath()<<endl;
    //QStringList
    app = url.encodedPath().split('/')[0];
    //app = list[0];
    if ( app.contains(".py")){
       app = "home";
    }
    ERR<<"INFO: LocalApp::readAppName(): App: "<<app<<endl;
#else
    ERR<<"INFO: LocalApp::readAppName(): Path: "<<url.path()<<endl;
    app = url.path().split('/')[0];
    if ( app.contains(".py") || app.contains(".")){
        app = "home";
    }
    ERR<<"INFO: LocalApp::readAppName(): App: "<<app<<endl;
    ERR<<"INFO: LocalApp::readAppName(): Path: "<<url.path()<<endl;
#endif
    return app;
}

void    LocalApp::getUrl( QUrl oldUrl , QUrl &newUrl){


    QString scriptName;
#ifndef USE_QT5
#ifdef WINDOWS
    scriptName   = home+"\\" + oldUrl.encodedPath();
#else
    scriptName   = home+"/" + oldUrl.encodedPath();
#endif
    //scriptName   = tmpUrl.toString(FULLPATH);
#else
#ifdef WINDOWS
    scriptName   = home+"\\" + oldUrl.path();
#else
    scriptName   = home+"/" + oldUrl.path();
#endif
    //scriptName   = tmpUrl.toDisplayString(QUrl::FullyDecoded);
    //scriptName.remove(0,6);
#endif
    if( QDir(scriptName).exists() ) {
#ifdef WINDOWS
        if( scriptName.at(scriptName.size()-1) == '/')
#else
        if( scriptName.at(scriptName.size()-1) == '\\')
#endif
            scriptName = scriptName + "index.py";
        else
#ifdef WINDOWS
            scriptName = scriptName + "\\index.py";
#else
            scriptName = scriptName + "/index.py";
#endif
    }
    if ( !getScript(scriptName) ){
        QFileInfo qFileInfo(scriptName);
        if ( qFileInfo.fileName() == "index.py" ){
            scriptName = qFileInfo.dir().absolutePath() + "/index.html";
        }
    }
#ifndef USE_QT5
    ERR<<"INFO: LocalApp::getUrl(): Encoded Path: "<<oldUrl.encodedPath()<<", "<<scriptName<<endl;
    newUrl.setPath(scriptName);
#else
    ERR<<"INFO: LocalApp::getUrl(): Path: "<<oldUrl.path()<<", "<<scriptName<<endl;
    newUrl.setPath(scriptName);
#endif
}

bool LocalApp::isScript(QString file){
    QString fext = QFileInfo(file).suffix();
    if ( fext == "py" ){
        QLibrary *lib = mapScriptToSo[QFileInfo(file).fileName()];
        if ( lib ) {
            ERR<<"INFO: LocalApp::isScript(): Script File : "<<file<<", "<<fext<<endl;
            return true;
        } else {
            ERR<<"INFO: LocalApp::isScript(): Unknown Script File : "<<file<<", "<<fext<<endl;
            return false;
        }

    } else {
        ERR<<"INFO: LocalApp::isScript(): Not Script File : "<<file<<", "<<fext<<endl;
        return false;
    }
}

bool LocalApp::isForbidden(QString file){
    QString fext = QFileInfo(file).suffix();
    if ( suffixFilter.contains(fext)){
        ERR<<"INFO: LocalApp::isForbidden(): Forbidden file "<<endl;
        return true;
    } else {
        ERR<<"INFO: LocalApp::isForbidden(): Not Forbidden file "<<endl;
        return false;
    }
}

QLibrary *LocalApp::getScript(QString file){
    QLibrary *lib = mapScriptToSo[QFileInfo(file).fileName()];
    return lib;
}

void LocalApp::decReferenceCount(){
    if( referenceCount == 0)
        return;
    referenceCount--;
}

void LocalApp::incReferenceCount(){
    referenceCount++;
}

LocalApp * LocalApp::getApp(QString appName){
    ERR<<"DBUG: LocalApp::getApp() : "<<appName<<endl;
    mapMutex.lock();
    LocalApp *tmp = mapNameToApp[appName];
    mapMutex.unlock();
    if ( tmp )
        return tmp;
    else
        return 0;
}

void       LocalApp::addApp(QString appName, LocalApp *app){
    mapMutex.lock();
    LocalApp *tmp = mapNameToApp[appName];
    if ( !tmp ){
        mapNameToApp[appName] = app;
    }
    mapMutex.unlock();
}

void       LocalApp::delApp(QString appName){
    mapMutex.lock();
    LocalApp *tmp = mapNameToApp[appName];
    if ( tmp ){
        mapNameToApp[appName] = 0;
        delete tmp;
    }
    mapMutex.unlock();
}
