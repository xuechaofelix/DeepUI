#include "networklayerdata.h"
#include <QDebug>

NetworkLayerData::NetworkLayerData(QString name,QString layerType)
{
    this->name = name;
    this->layerType = layerType;

}

QString NetworkLayerData::getName()
{
    return this->name;
}


void NetworkLayerData::insertRowHeadName(QString name)
{
    this->rowHeadNames->append(name);
    QVector<QString>* rowTmp = new QVector<QString>();
    int columnSize = this->columnHeadNames->size();
    for(int i=0;i<columnSize;i++){
        rowTmp->append("0");
    }
    data->append(rowTmp);
}
void NetworkLayerData::insertColumnHeadName(QString name)
{
    this->columnHeadNames->append(name);
    int rowSize = this->rowHeadNames->size();
    for(int i=0;i<rowSize;i++){
        data->at(i)->append("0");
    }
}
void NetworkLayerData::setData(int row, int column, QString data)
{
    if(row >= this->rowHeadNames->size() || column > this->columnHeadNames->size()){
        qDebug() << "Invalid setting data";
        return;
    }
    this->data->at(row)->replace(column,data);
}

bool NetworkLayerData::containsRowHeadName(QString name)
{
    return this->rowHeadNames->contains(name);
}
bool NetworkLayerData::containsColumnHeadName(QString name)
{
    return this->columnHeadNames->contains(name);
}

int NetworkLayerData::getRowSize()
{
    return this->rowHeadNames->size();
}
int NetworkLayerData::getColumnSize()
{
    return this->columnHeadNames->size();
}

int NetworkLayerData::indexOfRowHead(QString name)
{
    return this->rowHeadNames->indexOf(name);
}
int NetworkLayerData::indexOfColumnHead(QString name)
{
    return this->columnHeadNames->indexOf(name);
}

QString NetworkLayerData::getData(int row, int column)
{
    return this->data->at(row)->at(column);
}

QString NetworkLayerData::getRowHeadName(int index){
    return this->rowHeadNames->at(index);
}
QString NetworkLayerData::getColumnHeadName(int index){
    return this->columnHeadNames->at(index);
}
int NetworkLayerData::getRowHeadNames(QStringList * result)
{
    if(result == nullptr) return -1;
    for(int i=0;i<this->getRowSize();i++){
        result->append(this->rowHeadNames->at(i));
    }
    return 0;
}
int NetworkLayerData::getColumnHeadNames(QStringList * result)
{
    if(result == nullptr) return -1;
    for(int i=0;i<this->getColumnSize();i++){
        result->append(this->columnHeadNames->at(i));
    }
    return 0;
}

QString NetworkLayerData::getLayerType()
{
    return this->layerType;
}
