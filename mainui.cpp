#include "mainui.h"
#include "ui_mainui.h"
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QDebug>
#include "util.h"
#include <QJsonArray>
#include <QDir>
#include "selectdialog.h"
#include <QDialog>
#include "util.h"

MainUI::MainUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUI)
{
    ui->setupUi(this);
    this->initUI();

    QDir dir = QDir::tempPath();
    backend = new BackEnd(dir.absoluteFilePath("deepsymbol"));

   // backend = new BackEnd("/home/xuechao/xuechao/work/Lab/DeepAI/deepsymbol/deepsymbol");
    connect(backend, SIGNAL(sendOut(char * )), this,SLOT(on_readoutput(char *)) );
    connect(backend, SIGNAL(finished(int)), this, SLOT(verifyFinished(int)));
    //this->resultView->parsingJsonFile(JSON_RESULT_FILE);
}

void MainUI::initUI()
{
    this->projectView = new ProjectView();

    this->outView = new OutView();
    this->settingView = new SettingView();
    this->resultView = new ResultView();

    this->ui->splitterMain->setStretchFactor(0,1);
    this->ui->splitterMain->setStretchFactor(1,10);
    this->ui->splitterMain->setChildrenCollapsible(false);
    this->ui->splitterMain->setMinimumWidth(this->size().width()*2/10);

    this->ui->splitterOut->setStretchFactor(0,30);
    this->ui->splitterOut->setStretchFactor(1,1);
    this->ui->splitterOut->setChildrenCollapsible(false);
    this->ui->splitterOut->setMinimumHeight(this->size().height()*5/10);

    this->ui->splitterResult->setStretchFactor(0,3);
    this->ui->splitterResult->setStretchFactor(1,2);
    this->ui->splitterResult->setChildrenCollapsible(false);
    this->ui->splitterResult->setMinimumWidth(this->size().width()*5/10);

    this->ui->projectView->addWidget(this->projectView);
    this->ui->setView->addWidget(settingView);
    this->ui->resultView->addWidget(resultView);
    this->ui->outView->addWidget(this->outView);

    //ui->centralwidget->createWinId()
    //ui->centralwidget->setLayout(mainLayout);
    //setLayout(mainLayout);
    //this->ui->test->addWidget(settingView);


    //this->ui->centralwidget->

    //this->ui->Setting->addTab(nt, "Network");

    connect(this->projectView,SIGNAL(SIGNAL_OpenProject(Project *)),this->settingView, SLOT(openProject(Project *)));
    connect(this->projectView,SIGNAL(SIGNAL_CloseProject()), this->settingView, SLOT(closeProject()));
    connect(this->projectView,SIGNAL(SIGNAL_networkChanged(QString, QString)),this->settingView, SLOT(on_networkFileChanged(QString,QString)));
    connect(this->projectView,SIGNAL(SIGNAL_inputChanged(QString,QString)), this->settingView, SLOT(on_inputFileChanged(QString,QString)));
    connect(this->projectView,SIGNAL(SIGNAL_addTool(QString,Project *)),this->settingView, SLOT(on_addTool(QString, Project *)));
    connect(this->projectView,SIGNAL(SIGNAL_removeTool(QString)), this->settingView, SLOT(on_removeTool(QString)));


    connect(this->settingView,SIGNAL(SIGNAL_importNetwork()), this->projectView, SLOT(on_importNetwork()));
    connect(this->settingView,SIGNAL(SIGNAL_importInput()),this->projectView,SLOT(on_importInput()));

    connect(this->settingView,SIGNAL(SIGNAL_run()),this,SLOT(on_verify()));
    connect(this->resultView,SIGNAL(updateNetworkNodeStatus(QJsonObject)),this->settingView,SLOT(on_updateNetworkNodeStatus(QJsonObject)));

}
void MainUI::Run(){
 if(!this->projectView->isValidProject()) return;
 QString projectParameters = this->projectView->getProjectParameters();
 QString othersParameters = " --robust "+this->settingView->getRobustnessType()+
                            " --delta "+ QString::number(this->settingView->getDelta()) +
                            " --dumpJSON "+JSON_RESULT_FILE;

 backend->setCurrentParametersList(projectParameters+" "+othersParameters);


 this->outView->clear();
 backend->run();
}

void MainUI::verifyFinished(int exitCode)
{
    if(exitCode == 0)
        this->resultView->parsingJsonFile(JSON_RESULT_FILE);
}
QString MainUI::parsingFinalResult()
{
    QString result = "";
    QJsonObject * jsonObj = Util::parseJsonFile(JSON_RESULT_FILE);
    if(jsonObj==nullptr) return "Parsing JSON file failed";
    int nodes = 0;
    if(jsonObj->contains("number_of_nodes")){
        nodes = jsonObj->value("number_of_nodes").toInt();
    }
    if(jsonObj->contains("edges"))
    {
        QJsonValue value = jsonObj->value("edges");
        if(value.isArray())
        {
            QJsonArray array = value.toArray();
            for(int i=0;i<array.size();i++){
                result += "from "+array.at(i).toObject().value("from").toString()+
                          " to " + array.at(i).toObject().value("to").toString()+"\n";
            }
        }
    }
    return result;
}
void MainUI::on_readoutput(char * out)
{
    QString str(out);
    QList<QString> result = this->filter(str);
    //ui->outText->append(result);
    for(QString line : result){
        this->outView->appendText(line);
    }
}
QList<QString> MainUI::filter(QString out){
    QList<QString> lines = out.split("\n");
    QList<QString> result;
    QString line;
    int currentLevel = 0;
    for(int i=0;i<lines.size()-1;i++){
    //foreach (line, lines) {
        line = lines.at(i);
        line = line.trimmed();
        /*if(line.startsWith("[Info]")){
            currentLevel = 0;
        }
        else if(line.startsWith("[Worning]")){
            currentLevel = 1;

        }
        else if(line.startsWith("[Error]"))
        {
            currentLevel = 2;
        }
        if(currentLevel >= this->filterLevel)*/{
            result.append(line+"\n");
        }
    }
    /*if(currentLevel >= this->filterLevel)*/{
        result.append(lines.at(lines.size()-1));
    }
    return result;
}



MainUI::~MainUI()
{
    delete ui;
}


void MainUI::on_verify()
{
    this->Run();
}
void MainUI::closeEvent(QCloseEvent *event)
{
    this->projectView->closeProject();
}
void MainUI::on_action_New_Project_triggered()
{
    this->projectView->newProject();
}

void MainUI::on_action_Open_Project_triggered()
{
    this->projectView->openProject();
}

void MainUI::on_actionClose_Project_triggered()
{
    this->projectView->closeProject();
}

void MainUI::on_actionRun_triggered()
{
    this->Run();
}

void MainUI::on_actionAdd_Tool_triggered()
{
    this->projectView->addTool();
}

void MainUI::on_actionRemove_Tool_triggered()
{
    this->projectView->removeTool();
}

void MainUI::on_actionImport_Network_triggered()
{
    this->projectView->addNetwork();
}

void MainUI::on_actionImport_Input_triggered()
{
    this->projectView->addInput();
}
