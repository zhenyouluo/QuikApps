#include <QApplication>
#include <QtGui>
#include <QtGlobal>
#include <QLibrary>
#include <global.h>
#include "qfileerror.h"
#include "mainwindow.h"
#include "localapp.h"
//#include <Python.h> // Python Removal

QFile *error;
QTextStream *err;
QByteArray  home;
QByteArray  tmp;


void loadAppPlugins(){
    QFile *appCfgFile = new QFile(home+"/app.cfg");
#ifndef USE_QT5
    if ( ! appCfgFile->open(QIODevice::ReadOnly) ){
#else
    if ( ! appCfgFile->open(QFile::ReadOnly) ){
#endif
        ERR<<"ERRR: loadAppPlugins(): Unable to open app config file "<<endl;
    } else {
        ERR<<"ERRR: loadAppPlugins(): Opened app config file "<<endl;
        QByteArray appName;
        while ( (appName = appCfgFile->readLine() ).length() > 0 ){
#ifndef WINDOWS
            /*
             * Removing \n on unixes
             */
            //appName.remove(appName.length()-1, 1);
            appName.replace(QByteArray("\n"), QByteArray(""));
#else
            /*
             * Removing \r\n on windows
             */
            //appName.remove(appName.length()-2, 2);
            appName.replace(QByteArray("\r\n"), QByteArray(""));
#endif
            LocalApp* tmpApp = LocalApp::getApp(QString(appName));
            if(!tmpApp){
                ERR<<"DBUG: loadAppPlugins(): Creating new local app : "<<QString(appName)<<endl;
                tmpApp = new LocalApp(0,QString(appName));
                LocalApp::addApp(QString(appName), tmpApp);
            } else {
                ERR<<"DBUG: loadAppPlugins(): Using existing app : "<<QString(appName)<<endl;
            }
        }
        appCfgFile->close();
    }
    delete appCfgFile;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    setupContentTypes();
    error = new QFile();
    error->open( 2, QIODevice::Truncate|QIODevice::WriteOnly|QIODevice::Text);
    err = new QTextStream(error);
    ERR<<"DBUG: main(): Started "<<endl;
#ifndef WINDOWS
    home = qgetenv("HOME");
    home.append("/Apps");
    tmp.append("/tmp");
#else
    home = qgetenv("APPDATA");
    //home = "C:/Dev";
    home.append("\\Apps");
    tmp  = qgetenv("TEMP");
#endif
    if( !QDir(home.data()).exists() ){
        ERR<<"DBUG: main(): Home doesn't exists, creating home' "<<endl;
        QDir().mkdir(home.data());
        //Copy home files here
    }
    //homeLocation = &home;
    ERR<<"DBUG: main(): Home path : "<<home.data()<<endl;
    loadAppPlugins();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();

    //QLibrary libertyPlugin(home+QString("/libLibertyPlugin.so.1.0.0"));
    //libertyPlugin.setLoadHints(QLibrary::ResolveAllSymbolsHint);
    //libertyPlugin.load();

    //ERR<<"DBUG: library: "<<libertyPlugin.fileName()<<endl;
    //ERR<<"DBUG: library: Loaded ?  "<<libertyPlugin.isLoaded()<<endl;
    //ERR<<"DBUG: library pointer : "<<(pluginfunction)(libertyPlugin.resolve("plugininit"))<<endl;
    //ERR<<"DBUG: library pointer : "<<(pluginfunction)(libertyPlugin.resolve("pluginexit"))<<endl;
    //ERR<<"DBUG: library pointer : "<<(pluginfunction)(libertyPlugin.resolve("pluginexecute"))<<endl;
    //typedef void (*pluginfunction)();
    //pluginfunction tmp = libertyPlugin.resolve("plugininit");
    //if ( tmp )
    //    tmp();
    //else
    //    ERR<<"ERRR: library: unable to resolve symbol"<<endl;

    //QLibrary tmpLib("/home/anoop/Apps/libLibertyPlugin.so.1.0.0");
    //tmpLib.load();
    //ERR<<"ERRR: main(): "<<tmpLib.errorString()<<endl;
    //ERR<<"INFO: main(): Library loaded ? "<<tmpLib.isLoaded()<<", " <<tmpLib.fileName()<<endl;

#if 0 //Python removal
    Py_SetProgramName((char*)"Liberty");
    Py_Initialize();
    PyEval_InitThreads();
    PyThreadState*   mainThreadState = PyThreadState_Get();
    PyEval_ReleaseLock();
#endif
    app.exec();

#if 0 //Python removal
    PyEval_RestoreThread(mainThreadState);
    Py_Finalize();
#endif
    return 0;
}
