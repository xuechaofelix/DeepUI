#include "matrix.h"
#include "ui_matrix.h"
#include <QDebug>

Matrix::Matrix(const QString name, QStringList * rowHeadName,QStringList * columnHeadName, bool isSetDefaultHeadName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Matrix)
{
    ui->setupUi(this);
    this->name = name;
    if(rowHeadName != nullptr)
    {
        this->rowNumber = rowHeadName->size();
        model->setRowCount(this->rowNumber);
        for(int i=0;i<this->rowNumber;i++)
        {
            QString headName = rowHeadName->at(i);
            model->setHeaderData(i,Qt::Vertical,headName);
            this->rowHeadName->append(headName);
        }
    }
    else
    {
        model->setRowCount(this->rowNumber);
        if(isSetDefaultHeadName)
        {
            model->setHeaderData(0,Qt::Vertical,"inf");
            model->setHeaderData(1,Qt::Vertical,"sup");
        }

    }
    if(columnHeadName != nullptr)
    {
        this->columnNumber = columnHeadName->size();
        model->setColumnCount(this->columnNumber);
        for(int i=0;i<this->columnNumber;i++)
        {
            QString headName = columnHeadName->at(i);
            model->setHeaderData(i,Qt::Horizontal,headName);
            this->columnHeadName->append(headName);
        }
    }
    else
    {
       model->setColumnCount(this->columnNumber);
       if(isSetDefaultHeadName){
           model->setHeaderData(0,Qt::Horizontal,"inf");
           model->setHeaderData(1,Qt::Horizontal,"sup");
       }
    }
    ui->matrix->setModel(this->model);

    this->ui->matrixName->setText(this->name);
    this->ui->matrixDimention->setText(QString::number(this->rowNumber)+"*"+ QString::number(this->columnNumber));

    ui->matrix->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->matrix->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}


bool Matrix::isSetRowHeadName()
{
    return this->rowHeadName->size()>0;
}
bool Matrix::isSetColumnHeadName()
{
    return this->columnHeadName->size()>0;
}

int Matrix::indexOfRow(QString rowHeadName)
{
    return this->rowHeadName->indexOf(rowHeadName);
}
int Matrix::indexOfColumn(QString columnHeadName)
{
    return this->columnHeadName->indexOf(columnHeadName);
}

void Matrix::setEditable(bool flag)
{
    if(flag){
        this->ui->matrix->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::AnyKeyPressed);
    }
    else{
        this->ui->matrix->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

QString Matrix::getData(int row,int column)
{
    return this->model->item(row,column)->text();
}

int Matrix::getRowNumber()
{
    return this->model->rowCount();
}
int Matrix::getColumnNumber()
{
    return this->model->columnCount();
}


QStringList * Matrix::getRowHeadNames()
{
    return this->rowHeadName;
}
QStringList * Matrix::getColumnHeadNames()
{
    return this->columnHeadName;
}

void Matrix::setItemColor(int row, int column, QColor color)
{
    this->model->item(row,column)->setBackground(QBrush(color));
}

int Matrix::setName(QString name)
{
    this->name = name;
    ui->matrixName->setText(name);
    return  0;
}
int Matrix::setDescription(QString description)
{
    ui->matrixDimention->setText(description);
    return 0;
}
int Matrix::setData(QString ** vecs, int rowNumber, int columnNumber)
{
    for(int i=0;i<rowNumber;i++)
    {
        for(int j=0;j<columnNumber;j++){
            this->insertItem(i,j,vecs[i][j]);
        }
    }
    return 0;
}
int Matrix::insertItem(int row,int column, QString value)
{
    QStandardItem *item = new QStandardItem(value);
    model->setItem(row,column,item);
    return 0;
}


Matrix::~Matrix()
{
    delete ui;
}

void Matrix::on_matrix_doubleClicked(const QModelIndex &index)
{
    emit onValueChanged();
}
