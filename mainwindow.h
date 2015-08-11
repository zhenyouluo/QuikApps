#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UiMainWindow.h"
#include <QMainWindow>
#include <QList>
#include <QVector>
#include <QUrl>

namespace Ui {
//typedef QList<QUrl*> UrlList;
//typedef QVector<UrlList*> UrlTabs;
typedef QVector<LocalView *> LocalViews;
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LocalView      *currentLocalView;
    LocalViews      localViews;
    int             currentTabLoadIndex;
    QUrl            linkClicked;

    void getCurrentLocalView();
    int  getCurrentTabIndex();
    int  getCurrentUrlListIndex();

private slots:
    //void on_link_clicked(QUrl);
    void on_help_clicked();
    void on_webView_loadStarted();
    void on_webView_loadProgress(int );
    void on_webView_loadFinished(bool );
    void on_tabWidget_tabCloseRequested(int index);
    void on_tabWidget_currentChanged(int index);
    void on_lineEdit_returnPressed();
    void on_tabWidget_destroyed();
    void on_addBtn_clicked();
    void on_backBtn_clicked();
    void on_forwardBtn_clicked();
    void on_refreshBtn_clicked();
    void on_stopBtn_clicked();
    void on_goBtn_clicked();
    void on_homeBtn_clicked();
    //void on_openLinkInNewWindow_triggered();

};

#endif // MAINWINDOW_H
