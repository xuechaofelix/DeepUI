#ifndef MAINUI_H
#define MAINUI_H

#include <QMainWindow>
#include <QSplitter>

#include "settingview.h"
#include "projectview.h"
#include "outview.h"
#include "resultview.h"
#include "backend.h"

#include <QJsonObject>


#define JSON_RESULT_FILE "/tmp/Qt/temp.json"

namespace Ui {
class MainUI;
}

class MainUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainUI(QWidget *parent = nullptr);
    ~MainUI() ;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_action_New_Project_triggered();

    void on_action_Open_Project_triggered();

    void on_actionClose_Project_triggered();

    void on_readoutput(char * out);

    void on_actionRun_triggered();

    void verifyFinished(int exitCode);

    void on_verify();

    void on_actionAdd_Tool_triggered();

    void on_actionRemove_Tool_triggered();

    void on_actionImport_Network_triggered();

    void on_actionImport_Input_triggered();

private:
    Ui::MainUI * ui;
    SettingView * settingView;
    ProjectView * projectView;
    OutView * outView;
    ResultView * resultView;


    BackEnd * backend;

    void initUI();

    void Run();
    QList<QString> filter(QString out);
    QString parsingFinalResult();
};

#endif // MAINUI_H
