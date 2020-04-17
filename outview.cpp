#include "outview.h"
#include "ui_outview.h"
#include <QScrollBar>

OutView::OutView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutView)
{
    ui->setupUi(this);
}


void OutView::clear()
{
    this->ui->output->setText("");
}

void OutView::setText(QString content)
{
    this->ui->output->setText(content);
    QScrollBar *scrollbar = this->ui->output->verticalScrollBar();
    if(scrollbar){
        scrollbar->setSliderPosition(scrollbar->maximum());
    }
}

void OutView::appendText(QString content)
{
    this->ui->output->insertPlainText(content);
    QScrollBar *scrollbar = this->ui->output->verticalScrollBar();
    if(scrollbar){
        scrollbar->setSliderPosition(scrollbar->maximum());
    }
}

OutView::~OutView()
{
    delete ui;
}
