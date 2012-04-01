#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qiddlerpipetablemodel.h"
#include "proxy/rypipedata.h"
#include <QSettings>
#include <QWebFrame>
#include <QFileDialog>
#include <QDebug>

#include <QScriptEngine>
#include <QScriptValue>

#include "rule/ryrulemanager.h"
#include "proxy/ryproxyserver.h"

#include <QScriptEngine>

using namespace rule;

namespace Ui {
    class MainWindow;
}
class RyPipeData;
class QItemSelectionModel;
class RyJsBridge:public QObject{
        Q_OBJECT
    public:
        RyJsBridge();

    public slots:
        QString doAction(int action,const QString msg,quint64 groupId=0);
        QString getFile();
        QString getDir();
        QString getConfigs();

   signals:
        void ruleChanged(int action,QString json);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT


private slots:
        void toggleCapture();
        void showSettingsDialog();
public:
    explicit MainWindow(QWidget *parent=0);
    ~MainWindow();
public slots:
        void onNewPipe(RyPipeData_ptr);
        void onPipeUpdate(RyPipeData_ptr);

        void toggleProxy();

        void onSelectionChange(QModelIndex,QModelIndex);
        void onWaterfallActionTriggered();


public:
	typedef struct __proxyInfo{
		int enable;
		QString proxyString;
		QString pacUrl;
		QString isUsingPac;
	}ProxyInfo;
	QiddlerPipeTableModel pipeTableModel;

protected:
        void mousePressEvent(QMouseEvent *);
        void dragEnterEvent(QDragEnterEvent *);

private:
    Ui::MainWindow *ui;
    RyJsBridge *jsBridge;
    void createMenus();
    RyProxyServer *server;

    bool isUsingCapture;
    ProxyInfo previousProxyInfo;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *captureAct;
    QItemSelectionModel *itemSelectModel;
protected:
    void closeEvent(QCloseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    QSettings proxySetting;

private slots:
    void addJsObject();
};

#endif // MAINWINDOW_H
