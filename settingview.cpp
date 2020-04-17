#include "settingview.h"
#include "ui_settingview.h"
#include <QDebug>
#include <QJsonArray>

SettingView::SettingView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingView)
{
    ui->setupUi(this);

    connect(this->updateThread,SIGNAL(over()),this,SLOT(on_updateNetworkUIOver()));
}


void SettingView::initConfigurationView_S_L_Connection()
{
    connect(this->cfg,SIGNAL(run()),this,SLOT(verify()));
    connect(this->cfg,SIGNAL(SIGNAL_importNetwork()),this,SLOT(on_importNetwork()));
    connect(this->cfg,SIGNAL(SIGNAL_importInput()),this,SLOT(on_importInput()));
}


void SettingView::addTool(QString tool,Project * project)
{
    if(tool == TOOL_DEEPSYMBOL)
    {
        if(this->cfg){
            this->ui->setting->addTab(this->cfg,tool);
        }
        else
        {
            this->cfg = new ConfigurationView(project);
            initConfigurationView_S_L_Connection();
            this->ui->setting->addTab(this->cfg,tool);
        }
    }
}
 void SettingView::on_updateNetworkNodeStatus(QJsonObject obj)
 {
     if(!this->network->isLoaded()) return;
     if(obj.contains("layers"))
     {
         QJsonArray layers = obj.value("layers").toArray();
         int size = layers.size();
         for(int i=0;i<size;i++){
             QJsonObject layerStatus = layers.at(i).toObject();
             QString name = layerStatus.value("name").toString();
             QString type = layerStatus.value("type").toString();
             int numOfNeurons = layerStatus.value("number_of_neurons").toInt();
             int index = this->network->layerIndexOf(name);
             if(index == layerStatus.value("index").toString().toInt())
             {
                 QJsonObject::Iterator it;
                 QJsonObject node = layerStatus.value("bound_of_neurons").toObject();
                 for(it=node.begin();it!=node.end();it++)
                 {
                     QJsonObject bound =it.value().toObject();
                     QString nodeName =it.key();
                     this->network->setBoundOfNode(index,nodeName,bound.value("inf").toString(),bound.value("sup").toString());
                 }
            }
             else{
                 qDebug() << " layer index is not correct:"<<index <<layerStatus.value("index").toString().toInt();
             }

         }
     }
 }


 void SettingView::on_networkFileChanged(QString path,QString fileName)
 {
     if(this->cfg)
        this->cfg->changeNetworkFile(path,fileName);

     //this->network->loadNetworkfile(path,fileName);
     updateThread->setParameters(path,fileName);
     //this->loadWiget->show();
//     this->loadWiget= new LoadingWidget();
//     this->loadWiget->show();
     updateThread->start();
 }
 void SettingView::on_inputFileChanged(QString path,QString fileName)
 {
     if(this->cfg)
        this->cfg->changeInputFile(path,fileName);
 }

void SettingView::removeTool(QString tool)
{
    if(tool == TOOL_DEEPSYMBOL){
        if(!this->cfg) return;
        this->ui->setting->removeTab(this->ui->setting->indexOf(this->cfg));
        delete this->cfg;
        this->cfg= nullptr;
       // this->network->reload();
        //this->loadWiget->show();
//        this->loadWiget= new LoadingWidget();
//        this->loadWiget->show();
        this->updateThread->start();
    }
}

void SettingView::on_updateNetworkUIOver()
{
    qDebug() << "update network UI Ok";
    //this->loadWiget->hide();
    this->network->updateUI(this->updateThread->getLayers());
    //if(this->loadWiget)
      //  this->loadWiget->close();
}

void SettingView::on_addTool(QString tool, Project * p)
{
    this->addTool(tool,p);
}
void SettingView::on_removeTool(QString tool)
{
    this->removeTool(tool);
}



void SettingView::openProject(Project * p)
{
    if(p == nullptr)
    {
        qDebug() <<"setting view receive a invalid project";
        return;
    }
    //TODO: add network ....
    //this->network->loadNetworkfile(p->getPath(),p->getNetworkFileName());
   // updateThread->setParameters(p->getPath(),p->getNetworkFileName(),network);
    this->ui->setting->addTab(this->network, "network");

    for(int i=0;i<p->getTools()->size();i++)
    {
        this->addTool(p->getTools()->at(i),p);
    }

}


void SettingView::closeProject()
{

    this->ui->setting->clear();
    if(this->network){
        this->network->saveNetwork();
        delete  this->network;
    }
    if(this->cfg){
        delete this->cfg;
    }
}

double SettingView::getDelta()
{
    if(this->cfg == nullptr) return 0;
    return this->cfg->getDelta();
}
QString SettingView::getRobustnessType()
{
    if(this->cfg == nullptr) return "";
    return this->cfg->getRobustnessType();
}


void SettingView::verify()
{
    this->network->saveNetwork();
    emit SIGNAL_run();
}


void SettingView::on_importNetwork()
{
    emit this->SIGNAL_importNetwork();
}
void SettingView::on_importInput()
{
    emit this->SIGNAL_importInput();
}

SettingView::~SettingView()
{
    delete this->updateThread;
    delete ui;
}
