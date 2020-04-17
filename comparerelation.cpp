#include "comparerelation.h"
#include "ui_comparerelation.h"

CompareRelation::CompareRelation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompareRelation)
{
    ui->setupUi(this);
    graph = new GraphWidget();
    this->ui->Image->addWidget(graph);
}

void CompareRelation::addNode(QString name)
{
    this->graph->addNode(name);
}
void CompareRelation::addEdge(QString name1,QString name2)
{
    this->graph->addEdge(name1,name2);
}

void CompareRelation::clear()
{
    this->graph->clear();
}
CompareRelation::~CompareRelation()
{
    delete ui;
}
