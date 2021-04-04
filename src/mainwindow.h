#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QGraphicsOpacityEffect>
#include <QIcon>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QProgressBar>
#include <QRegExp>
#include <QSettings>
#include <QStatusBar>
#include <QStyle>
#include <QStyleFactory>
#include <QSystemTrayIcon>
#include <QWebEngineCookieStore>
#include <QWebEngineFullScreenRequest>
#include <QWebEngineProfile>
#include <QWebEngineView>
#include <QWebEngineSettings>

#include "notificationpopup.h"
#include "requestinterceptor.h"
#include "settingswidget.h"
#include "webenginepage.h"

#include "downloadmanagerwidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
public slots:
    void updateWindowTheme();
    void updatePageTheme();
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QPalette lightPalette;
    void createActions();
    void createStatusBar();
    void createTrayIcon();
    void createWebEngine();

    QSettings settings;

    QRegExp notificationsTitleRegExp;
    QIcon trayIconRead;
    QIcon trayIconUnread;

    QAction *reloadAction;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *aboutAction;
    QAction *settingsAction;
    QAction *quitAction;

    QMenu *trayIconMenu;
    QSystemTrayIcon *trayIcon;

    QWebEngineView *webEngine;
    QStatusBar *statusBar;


    SettingsWidget * settingsWidget = nullptr;

    //void reload();

    DownloadManagerWidget m_downloadManagerWidget;
    QScopedPointer<QWebEngineProfile> m_otrProfile;


private slots:

    void readSettings();
    void handleWebViewTitleChanged(QString title);
    void handleLoadStarted();
    void handleLoadProgress(int progress);
    void handleDownloadRequested(QWebEngineDownloadItem *download);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void messageClicked();
    void doReload();
    void showAbout();
    void notify(QString title, QString message);
    void showSettings();
    void handleCookieAdded(const QNetworkCookie &cookie);
    void handleLoadFinished(bool loaded);

    QString getPageTheme();
    void toggleMute(const bool checked);
    void doAppReload();
    void askToReloadPage();
    void updateSettingsUserAgentWidget();
    void fullScreenRequested(QWebEngineFullScreenRequest request);

    void createWebPage(bool offTheRecord =false);
    void init_settingWidget();
    void init_globalWebProfile();
};

#endif // MAINWINDOW_H