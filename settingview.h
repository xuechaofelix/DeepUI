#ifndef SETTINGVIEW_H
#define SETTINGVIEW_H

#include <QWidget>
#include "network.h"
#include "configurationview.h"
#include <QJsonObject>
#include "updatenetworkthread.h"
#include "loadingwidget.h"


namespace Ui {
class SettingView;
}

class SettingView : public QWidget
{
    Q_OBJECT

public:
    explicit SettingView(QWidget *parent = nullptr);
    ~SettingView();

    double getDelta();
    QString getRobustnessType();

public slots:
    void openProject(Project * p);
    void closeProject();
    void verify();
    void on_addTool(QString tool, Project* project);
    void on_removeTool(QString tool);
    void on_updateNetworkNodeStatus(QJsonObject obj);
    void on_networkFileChanged(QString path,QString fileName);//TODO
    void on_inputFileChanged(QString path,QString fileName);//TODO
    void on_importNetwork();
    void on_importInput();

    void on_updateNetworkUIOver();

private:
    Ui::SettingView *ui;

     Network * network = new Network();
    ConfigurationView * cfg = nullptr;
    UpdateNetworkThread * updateThread = new UpdateNetworkThread();
    LoadingWidget * loadWiget;
    void initConfigurationView_S_L_Connection();
    void addTool(QString tool,Project *p);
    void removeTool(QString tool);

signals:
    void SIGNAL_run();
    void SIGNAL_importNetwork();
    void SIGNAL_importInput();


};

#endif // SETTINGVIEW_H
