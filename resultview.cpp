#include "resultview.h"
#include "ui_resultview.h"
#include "util.h"
#include <QDebug>
#include <QJsonArray>

ResultView::ResultView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultView)
{
    ui->setupUi(this);
    this->resultGraph =  new CompareRelation();
    connect(ui->result,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));
}

void ResultView::showCompareRelation()
{
    if(this->ui->result->indexOf(this->resultGraph) == -1){
        this->ui->result->addTab(this->resultGraph,"Relation");
    }
}

void ResultView::parsingJsonFile(QString jsonFile)
{
    this->resultGraph->clear();
    this->showCompareRelation();

    QJsonObject * jsonObj = Util::parseJsonFile(jsonFile);
    if(jsonObj==nullptr) {
        qDebug() << "jsonObj is unvalid";
        return ;
    }
    emit this->updateNetworkNodeStatus(*jsonObj);
    if(jsonObj->contains("graph"))
    {
        QJsonObject graph = jsonObj->value("graph").toObject();
        int nodes = 0;
        if(graph.contains("number_of_nodes")){
            nodes = graph.value("number_of_nodes").toString().toInt();
            for(int i=0;i<nodes;i++)
            {
                //this->resultGraph->addNode(QString::number(i));
            }
        }
        QStringList names;
        if(graph.contains(("names")))
        {
            QJsonValue value = graph.value("names");
            if(value.isArray())
            {
                QJsonArray array = value.toArray();
                int size =array.size();
                for(int i=0;i<size;i++){
                    names.append(array.at(i).toString());
                    this->resultGraph->addNode(array.at(i).toString());
                }
            }
        }

        if(graph.contains("edges"))
        {
            QJsonValue value = graph.value("edges");
            if(value.isArray())
            {
                QJsonArray array = value.toArray();
                int size =array.size();
                for(int i=0;i<size;i++){
                    int indexFrom = array.at(i).toObject().value("from").toString().toInt();
                    int indexTo = array.at(i).toObject().value("to").toString().toInt();
                    this->resultGraph->addEdge(names.at(indexFrom),names.at(indexTo));

                }
            }
        }
    }


}


void ResultView::removeSubTab(int index)
{
    this->ui->result->removeTab(index);
}
ResultView::~ResultView()
{
    delete ui;
}
