#include "mainwindow.h"
#include "UiMainWindow.h"
#include "qfileerror.h"

class Ui_MainWindow *globalUi;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow)
{
    //ui = new Ui::MainWindow(this);
    ui->setupUi(this);
    globalUi = ui;
    currentLocalView = ui->webView;
    localViews.append(ui->webView);
    currentTabLoadIndex = 0;
    QIcon icon(":/icons/app32.png");
    setWindowIcon(icon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getCurrentLocalView(){
    int index = ui->tabWidget->currentIndex();
    if ( index < localViews.size())
        currentLocalView = localViews[index];
    else
        currentLocalView = 0;
    if(currentLocalView == 0)
        ERR<<"ERRR: MainWindow::getCurrentLocalView: Index out of range "<<endl;
}

int MainWindow::getCurrentTabIndex(){
   return  ui->tabWidget->currentIndex();
}

//using namespace Ui;
int MainWindow::getCurrentUrlListIndex(){

    return currentLocalView?currentLocalView->getCurrentListIndex():0;
}

void MainWindow::on_goBtn_clicked(){
    ERR<<"DBUG: MainWindow::on_goBtn_clicked"<<endl;
    currentTabLoadIndex = getCurrentTabIndex();
    QUrl *newUrl = new QUrl(ui->lineEdit->text());
    getCurrentLocalView();
    if( currentLocalView ){
        currentLocalView->loadStatus = 0;
        currentLocalView->loadUrl(newUrl, true);
#ifndef USE_QT5
        ui->lineEdit->setText(currentLocalView->url().toString(SCHEMEFULLPATH));
#else
        ui->lineEdit->setText(currentLocalView->url().toDisplayString(QUrl::FullyDecoded));
#endif
    } else {
        ERR<<"ERRR: MainWindow::on_goBtn_clicked: Index out of range"<<endl;
    }
}


void MainWindow::on_stopBtn_clicked()
{
    ERR<<"DBUG: MainWindow::on_stopBtn_clicked"<<endl;
    getCurrentLocalView();
    if(currentLocalView ){
        currentLocalView->stop();
        currentLocalView->loadStatus = 0;
    }else{
            ERR<<"ERRR: MainWindow::on_stopBtn_clicked: Index out of range"<<endl;
    }
}

void MainWindow::on_refreshBtn_clicked()
{
    ERR<<"DBUG: MainWindow::on_refreshBtn_clicked"<<endl;
    currentTabLoadIndex = getCurrentTabIndex();
    getCurrentLocalView();
    if(currentLocalView ) {
        //if( currentLocalView->loadStatus == 101){
            currentLocalView->loadStatus = 0;
            currentLocalView->reload();
#ifndef USE_QT5
            ui->lineEdit->setText(currentLocalView->url().toString(SCHEMEFULLPATH));
#else
            ui->lineEdit->setText(currentLocalView->url().toDisplayString(QUrl::FullyDecoded));
#endif
        //}
    }else{
        ERR<<"ERRR: MainWindow::on_refreshBtn_clicked: Index out of range"<<endl;
    }
}

void MainWindow::on_forwardBtn_clicked()
{
    ERR<<"DBUG: MainWindow::on_forwardBtn_clicked"<<endl;
    currentTabLoadIndex = getCurrentTabIndex();
    getCurrentLocalView();
    if(currentLocalView ) {
        currentLocalView->loadStatus = 0;
        currentLocalView->forward();
    }else{
        ERR<<"ERRR: MainWindow::on_forwardBtn_clicked: Index out of range"<<endl;
    }
}

void MainWindow::on_addBtn_clicked()
{
    ERR<<"DBUG: MainWindow::on_addBtn_clicked"<<endl;
    int index;
    localViews.append( ui->addNewTab(index) );
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::on_backBtn_clicked()
{
    ERR<<"DBUG: MainWindow::on_backBtn_clicked"<<endl;
    getCurrentLocalView();
    if(currentLocalView ) {
        currentLocalView->loadStatus = 0;
        currentTabLoadIndex = getCurrentTabIndex();
        currentLocalView->back();
    }else{
        ERR<<"ERRR: MainWindow::on_backBtn_clicked: Index out of range"<<endl;
    }
}

void MainWindow::on_homeBtn_clicked()
{
    ERR<<"DBUG: MainWindow::on_homeBtn_clicked"<<endl;
    getCurrentLocalView();
    if( currentLocalView ){
        currentLocalView->load(QUrl("local:home.py"));
    }else{
        ERR<<"ERRR: MainWindow::on_homeBtn_clicked: Index out of range"<<endl;
    }
}

void MainWindow::on_tabWidget_destroyed()
{
    ERR<<"DBUG: MainWindow::on_tabWidget_destroyed"<<endl;
}

void MainWindow::on_lineEdit_returnPressed()
{
    ERR<<"DBUG: MainWindow::on_lineEdit_returnPressed"<<endl;
    currentTabLoadIndex = getCurrentTabIndex();
    QUrl *newUrl = new QUrl(ui->lineEdit->text());
    getCurrentLocalView();
    if( currentLocalView ) {
        currentLocalView->loadUrl(newUrl, true);
#ifndef USE_QT5
        ui->lineEdit->setText(currentLocalView->url().toString(SCHEMEFULLPATH));
#else
        ui->lineEdit->setText(currentLocalView->url().toDisplayString(QUrl::FullyDecoded));
#endif
    }else{
        ERR<<"ERRR: MainWindow::on_lineEdit_returnPressed: Index out of range"<<endl;
    }
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ERR<<"DBUG: MainWindow::on_tabWidget_tabCloseRequested"<<endl;
    if(index != 0){
        QWidget *tmp =(QWidget*) ui->tabWidget->widget(index);
        ui->tabWidget->removeTab(index);
        if( index < localViews.size() ){
            localViews.remove(index);
        }else{
            ERR<<"ERRR: MainWindow::on_tabWidget_tabCloseRequested: Index out of range"<<endl;
        }
        delete tmp;
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    ERR<<"DBUG: MainWindow::on_tabWidget_currentChanged"<<endl;
    getCurrentLocalView();
    if( currentLocalView ){
#ifndef USE_QT5
        ui->lineEdit->setText(currentLocalView->url().toString(SCHEMEFULLPATH));
#else
        ui->lineEdit->setText(currentLocalView->url().toDisplayString(QUrl::FullyDecoded));
#endif
    }else{
        ERR<<"ERRR: MainWindow::on_tabWidget_currentChanged: Index out of range"<<endl;
    }
}

void MainWindow::on_webView_loadProgress(int value )
{
    getCurrentLocalView();
    if( currentLocalView ){
        currentLocalView->loadStatus = value;
        ui->statusBar->showMessage(QString("Loading Page... ")+QString("%1").arg(value)+QString("%"));
    }else {
        ERR<<"ERRR: MainWindow::on_webView_loadStarted: Index out of range"<<endl;
    }
}

void MainWindow::on_webView_loadFinished(bool value )
{
    ERR<<"DBUG: MainWindow::on_webView_loadFinished"<<endl;
#ifndef USE_QT5
        ui->lineEdit->setText(currentLocalView->url().toString(SCHEMEFULLPATH));
#else
        ui->lineEdit->setText(currentLocalView->url().toDisplayString(QUrl::FullyDecoded));
#endif
    if( currentLocalView ){
        currentLocalView->loadStatus = 101;
#ifndef USE_QT5
        ui->statusBar->showMessage(QString("Loaded ")+currentLocalView->url().toString(SCHEMEFULLPATH));
#else
        ui->statusBar->showMessage(QString("Loaded ")+currentLocalView->url().toDisplayString(QUrl::FullyDecoded));
#endif
    }else {
        ERR<<"ERRR: MainWindow::on_webView_loadFinished: Index out of range"<<endl;
    }
    if ( currentTabLoadIndex < localViews.size()){
        LocalView *tmpView = localViews[currentTabLoadIndex];
        if(tmpView != NULL){
            QString tmpStr = tmpView->title();
            tmpStr.truncate(16);
            if(tmpStr == ""){
                if( currentTabLoadIndex == 0 ){
                    tmpStr = "Home";
                } else {
                    tmpStr = "NewTab";
                }
            }
            ui->tabWidget->setTabText(currentTabLoadIndex, tmpStr );
        }
    }else{
        ERR<<"ERRR: MainWindow::on_webView_loadFinished: Index out of range"<<endl;
    }
}


void MainWindow::on_webView_loadStarted()
{
    ERR<<"DBUG: MainWindow::on_webView_loadStarted"<<endl;
    if( currentLocalView ){
        ui->statusBar->showMessage(QString("Loading Page..."));
    }else {
        ERR<<"ERRR: MainWindow::on_webView_loadStarted: Index out of range"<<endl;
    }
}

//void MainWindow::on_webView_urlChanged(QUrl url){
//    ERR<<"DBUG: MainWindow::on_webView_urlChanged"<<endl;
//}

void MainWindow::on_help_clicked()
{
    ERR<<"DBUG: MainWindow::on_help_clicked"<<endl;
    //ui->lineEdit->setText(url.toString());
}
