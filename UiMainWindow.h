#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QtCore/QVariant>
#ifdef USE_QT5
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWebKitWidgets/QWebView>
#else
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QtWebKit/QWebView>
#endif
#include <QVector>
#include "localview.h"

typedef QVector<LocalView *> LocalViews;

#include "qfileerror.h"
#include "localview.h"
#include "mimetypes.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow:public QWidget
{
    //Q_OBJECT

public:
    //LocalViews localViews;
    QAction *actionExit;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionCopy_Link;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionBookmarks;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *addBtn;
    QPushButton *backBtn;
    QPushButton *forwardBtn;
    QPushButton *refreshBtn;
    QPushButton *stopBtn;
    QPushButton *homeBtn;
    QLineEdit *lineEdit;
    QPushButton *goBtn;
    QTabWidget *tabWidget;
    QWidget *homeTab;
    QHBoxLayout *horizontalLayout_2;
    //QWebView *webView;
    LocalView *webView;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0,0,0,0); //setContentsMargins(0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0,0,0,0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addBtn = new QPushButton(centralWidget);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));
        QIcon icon0;
        icon0.addFile(QString::fromUtf8(":/icons/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addBtn->setIcon(icon0);
        addBtn->setIconSize(QSize(20, 20));
        horizontalLayout->addWidget(addBtn);

        backBtn = new QPushButton(centralWidget);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        backBtn->setIcon(icon);
        backBtn->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(backBtn);

        forwardBtn = new QPushButton(centralWidget);
        forwardBtn->setObjectName(QString::fromUtf8("forwardBtn"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        forwardBtn->setIcon(icon1);
        forwardBtn->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(forwardBtn);

        refreshBtn = new QPushButton(centralWidget);
        refreshBtn->setObjectName(QString::fromUtf8("refreshBtn"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        refreshBtn->setIcon(icon2);
        refreshBtn->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(refreshBtn);

        stopBtn = new QPushButton(centralWidget);
        stopBtn->setObjectName(QString::fromUtf8("stopBtn"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopBtn->setIcon(icon3);
        stopBtn->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(stopBtn);



        homeBtn = new QPushButton(centralWidget);
        homeBtn->setObjectName(QString::fromUtf8("homeBtn"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/home.png"), QSize(), QIcon::Normal, QIcon::Off);
        homeBtn->setIcon(icon4);
        homeBtn->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(homeBtn);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QFont font;
        font.setPointSize(10);
        lineEdit->setFont(font);

        horizontalLayout->addWidget(lineEdit);

        goBtn = new QPushButton(centralWidget);
        goBtn->setObjectName(QString::fromUtf8("goBtn"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/go.png"), QSize(), QIcon::Normal, QIcon::Off);
        goBtn->setIcon(icon5);
        goBtn->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(goBtn);

        backBtn->setFlat(true);
        forwardBtn->setFlat(true);
        refreshBtn->setFlat(true);
        addBtn->setFlat(true);
        stopBtn->setFlat(true);
        goBtn->setFlat(true);
        homeBtn->setFlat(true);

        verticalLayout_2->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(true);

        //tabWidget->setMovable(true);
        homeTab = new QWidget();
        homeTab->setObjectName(QString::fromUtf8("homeTab"));
        horizontalLayout_2 = new QHBoxLayout(homeTab);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0,0,0,0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        //QUrl *Url = new QUrl("local:///D:/toi.py?a=123&b=hello&c=world");
        QUrl *Url = new QUrl("local:home.py");
#ifndef USE_QT5
        ERR<<"DBUG: Ui_MainWindow::SetupUi(): Path:  "<<Url->encodedPath()<<endl;
        ERR<<"DBUG: Ui_MainWindow::SetupUi(): Query: "<<Url->encodedQuery()<<endl;
#else
        ERR<<"DBUG: Ui_MainWindow::SetupUi(): Path:  "<<Url->path()<<endl;
        ERR<<"DBUG: Ui_MainWindow::SetupUi(): Query: "<<Url->query()<<endl;
#endif
        lineEdit->setText(Url->toString());
        webView = new LocalView(homeTab);

        webView->setObjectName(QString::fromUtf8("homeView"));
        webView->loadUrl(Url, false);
        horizontalLayout_2->addWidget(webView);
        tabWidget->addTab(homeTab, QString("Home"));
        verticalLayout_2->addWidget(tabWidget);
        verticalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));

        MainWindow->setStatusBar(statusBar);
        tabWidget->setCurrentIndex(0);
        mainWindow = MainWindow;
        QMetaObject::connectSlotsByName(MainWindow);
        connectLocalViewSignals(webView);

        //addNewTab();
    } // setupUi

private:

    QMainWindow *mainWindow;

    void connectLocalViewSignals(LocalView *local){
        connect(local,SIGNAL(loadStarted()),     mainWindow,SLOT(on_webView_loadStarted()));
        connect(local,SIGNAL(loadFinished(bool)),mainWindow,SLOT(on_webView_loadFinished(bool)));
    }


private slots:





public:

    LocalView* addNewTab(int &index){
        //char buf[16];
        QWidget *tmpTab = new QWidget();
        tmpTab->setObjectName(QString("NotHomeTab"));
        QHBoxLayout *tmpHbox = new QHBoxLayout(tmpTab);
        tmpHbox->setContentsMargins(0,0,0,0);
        tmpHbox->setSpacing(0);
        LocalView *tmpWebView = new LocalView(tmpTab);
        tmpHbox->addWidget(tmpWebView);
        tmpWebView->setObjectName(QString("NotHomeWebView"));
        index = tabWidget->addTab(tmpTab, QString("New Tab"));
        tabWidget->setCurrentIndex(index);
        connectLocalViewSignals(tmpWebView);
        return tmpWebView;
    }

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionCut->setText(QApplication::translate("MainWindow", "Cut", 0));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0));
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", 0));
        actionCopy_Link->setText(QApplication::translate("MainWindow", "Options", 0));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionBookmarks->setText(QApplication::translate("MainWindow", "Bookmarks", 0));
        backBtn->setText(QString());
        forwardBtn->setText(QString());
        refreshBtn->setText(QString());
        stopBtn->setText(QString());
        goBtn->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(homeTab), QApplication::translate("MainWindow", "Home", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi


};

namespace Ui {
    class MainWindow: public Ui_MainWindow {
    };
} // namespace Ui

QT_END_NAMESPACE



#endif // UIMAINWINDOW_H
