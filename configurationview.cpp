#include "configurationview.h"
#include "ui_configurationview.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QtMath>
ConfigurationView::ConfigurationView(Project * pro, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigurationView)
{
    ui->setupUi(this);
    if(pro == nullptr)
    {
        qDebug() << "project is null";
        return;
    }
    this->project = pro;
    this->changeNetworkFile(this->project->getPath(),this->project->getNetworkFileName());
    this->changeInputFile(this->project->getPath(),this->project->getInputFileName());



    //spin and slide
    ui->deltaSpin->setRange(0,1);
    ui->deltaSlider->setRange(0,(int)pow(10,UI_DELTA_PRECISION));
    ui->deltaSpin->setSingleStep(pow(0.1,UI_DELTA_PRECISION));
    ui->deltaSpin->setDecimals(UI_DELTA_PRECISION);
    connect(ui->deltaSlider, SIGNAL(valueChanged(int)), this, SLOT(changeSpinboxValue(int)));
    connect(ui->deltaSpin, SIGNAL(valueChanged(double)), this, SLOT(changeSlideValue(double)));

}

void ConfigurationView::importNetwork()
{
    emit SIGNAL_importNetwork();
}

void ConfigurationView::importInputFile()
{
    emit SIGNAL_importInput();
}

ConfigurationView::~ConfigurationView()
{
    delete ui;
}


QString ConfigurationView::getRobustnessType()
{
    return this->roubustnessType;
}

double ConfigurationView::getDelta()
{
    return this->ui->deltaSpin->value();
}

void ConfigurationView::changeSlideValue(double value)
{
    ui->deltaSlider->setValue((int)(value * pow(10,UI_DELTA_PRECISION)));
}
void ConfigurationView::changeSpinboxValue(int value)
{
    ui->deltaSpin->setValue(value*pow(0.1,UI_DELTA_PRECISION));
}


void ConfigurationView::changeNetworkFile(QString path, QString fileName)
{
    QDir dir(path);
    this->ui->networkFile->setText(dir.absoluteFilePath(fileName));
    this->ui->networkFile->setCursorPosition(0);
}
void ConfigurationView::changeInputFile(QString path, QString fileName)
{
    QDir dir(path);
    this->ui->inputFile->setText(dir.absoluteFilePath(fileName));
    this->ui->inputFile->setCursorPosition(0);
}

void ConfigurationView::on_importNetwork_clicked()
{
    this->importNetwork();
}


void ConfigurationView::on_chooseInput_clicked()
{
    this->importInputFile();
}

void ConfigurationView::on_robustnessType_currentIndexChanged(const QString &arg1)
{
    this->roubustnessType = arg1;
}

void ConfigurationView::on_run_clicked()
{
    emit run();
}
