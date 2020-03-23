#include "ui_plugin.h"
#include "ui_ui_plugin.h"
#include <QDebug>
#include <QFile>
#include "util.h"

UI_Plugin::UI_Plugin(QString dataFilePath, QString unaddedPluginFileName, QString addedPluginFileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UI_Plugin)
{
    ui->setupUi(this);

    this->dataFilePath = dataFilePath;
    this->unaddedPluginFileName = unaddedPluginFileName;
    this->addedPluginFileName = addedPluginFileName;

    QStringList * unAddedPlugin = new QStringList();
    QStringList * addedPlugin= new QStringList();

    this->loadPlugin(unAddedPlugin, addedPlugin);

    unAddedModel = new QStringListModel(this);
    addedModel = new QStringListModel(this);


    unAddedModel->setStringList(*unAddedPlugin);
    addedModel->setStringList(*addedPlugin);


    ui->unadded_list->setModel(unAddedModel);
    ui->added_list->setModel(addedModel);

    ui->unadded_list->setEditTriggers(QAbstractItemView:: NoEditTriggers);
    ui->added_list->setEditTriggers(QAbstractItemView:: NoEditTriggers);

    ui->addPlugin->setEnabled(false);
    ui->removePlugin->setEnabled(false);
    ui->up->setEnabled(false);
    ui->down->setEnabled(false);
    ui->top->setEnabled(false);
    ui->bottom->setEnabled(false);

    ui->unadded_list->setContextMenuPolicy(Qt::CustomContextMenu);
    cmenu = new QMenu(ui->unadded_list);
    QAction *importAction = cmenu->addAction("Import");
    QAction *deleteAction = cmenu->addAction("Delete");

    connect(importAction, SIGNAL(triggered(bool)), this, SLOT(importNewPlugin()));
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(deletePlugin()));

}
QStringList readFile(QString filePath, QString fileName)
{
    QDir path(filePath);

    QFile file(path.absoluteFilePath(fileName));
    QStringList result;
    if (!file.open(QFile::ReadOnly))
        return result;

#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList plugin;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            result.append(line.trimmed());
    }

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
    file.close();
    return result;
}
void UI_Plugin::loadPlugin(QStringList * unAddedPlugin, QStringList * addedPlugin){
    unAddedPlugin->append(readFile(this->dataFilePath, this->unaddedPluginFileName));
    addedPlugin->append(readFile(this->dataFilePath, this->addedPluginFileName));
}

bool writeFile(QString filePath, QString fileName, QStringList  list){
    QDir path(filePath);

    QFile file(path.absoluteFilePath(fileName));
    qDebug()<<fileName;
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    for(int i=0;i<list.size();i++)
    {
        out << list.at(i) << "\n";
    }
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
    out.flush();

    file.close();
    //setCurrentFile(fileName);
   return true;
}

void UI_Plugin::savePlugin(){
    Util::createFile(this->dataFilePath, this->unaddedPluginFileName);
   bool flag =  writeFile(this->dataFilePath,this->unaddedPluginFileName,this->unAddedModel->stringList());
   Util::createFile(this->dataFilePath,this->addedPluginFileName);
   bool flag1 =  writeFile(this->dataFilePath,this->addedPluginFileName,this->addedModel->stringList());
   qDebug() << flag << flag1;
}

void UI_Plugin::importNewPlugin()
{
    Choose * chooseFiles = new Choose("Choose Plugin", true);
    if(chooseFiles->exec() ==  QDialog::Accepted){

        QString files = chooseFiles->getValue();
        QStringList fileList = files.split(";");
        for(int i=0;i<fileList.size()-1;i++){
            qDebug() << fileList.at(i);
            QString data = fileList.at(i);
           //add new row
               unAddedModel->insertRow(unAddedModel->rowCount());
               QModelIndex index =unAddedModel->index(unAddedModel->rowCount()-1,0);
               unAddedModel->setData(index,data,Qt::DisplayRole);
               ui->unadded_list->setCurrentIndex(index);

               ui->addPlugin->setEnabled(true);


        }


    }
    return;

}


void UI_Plugin::deletePlugin(){
    QModelIndex  index;
    index=ui->unadded_list->currentIndex(); //获取当前 modelIndex
    QString data = unAddedModel->data(index).toString();
    unAddedModel->removeRow(index.row()); //删除当前行
    if(unAddedModel->rowCount() == 0) ui->addPlugin->setEnabled(false);

}
UI_Plugin::~UI_Plugin()
{
    delete ui;
}

void UI_Plugin::closeEvent(QCloseEvent *event)
{
    this->savePlugin();
}

void UI_Plugin::on_addPlugin_clicked()
{
    QModelIndex  index;
    index=ui->unadded_list->currentIndex(); //获取当前 modelIndex
    QString data = unAddedModel->data(index).toString();
   if( unAddedModel->removeRow(index.row())) //删除当前行
   {
       if(unAddedModel->rowCount() == 0) ui->addPlugin->setEnabled(false);
       addedModel->insertRow(addedModel->rowCount());
       QModelIndex index2 =addedModel->index(addedModel->rowCount()-1,0);
       addedModel->setData(index2,data,Qt::DisplayRole);
       ui->added_list->setCurrentIndex(index2);

       ui->removePlugin->setEnabled(true);
       ui->up->setEnabled(true);
       ui->down->setEnabled(false);
       ui->top->setEnabled(true);
       ui->bottom->setEnabled(false);

       if(addedModel->rowCount()==1 || addedModel->rowCount() == 0){
           ui->up->setEnabled(false);
           ui->top->setEnabled(false);
           ui->down->setEnabled(false);
           ui->bottom->setEnabled(false);
       }
   }
}

void UI_Plugin::on_removePlugin_clicked()
{
    QModelIndex  index;
    index=ui->added_list->currentIndex(); //获取当前 modelIndex
    QString data = addedModel->data(index).toString();
   if( addedModel->removeRow(index.row())) //删除当前行
   {
       if(addedModel->rowCount()==0)
       {
           ui->removePlugin->setEnabled(false);
           ui->up->setEnabled(false);
           ui->down->setEnabled(false);
           ui->top->setEnabled(false);
           ui->bottom->setEnabled(false);
       }
       if(addedModel->rowCount()==ui->added_list->currentIndex().row()+1)
       {
           ui->bottom->setEnabled(false);
           ui->down->setEnabled(false);
       }
       unAddedModel->insertRow(unAddedModel->rowCount());
       QModelIndex index2 =unAddedModel->index(unAddedModel->rowCount()-1,0);
       unAddedModel->setData(index2,data,Qt::DisplayRole);
       ui->unadded_list->setCurrentIndex(index2);

       ui->addPlugin->setEnabled(true);

       if(addedModel->rowCount()==1 || addedModel->rowCount() == 0){
           ui->up->setEnabled(false);
           ui->top->setEnabled(false);
           ui->down->setEnabled(false);
           ui->bottom->setEnabled(false);
       }
   }
}

void UI_Plugin::on_bottom_clicked()
{
    QModelIndex  index;
    index=ui->added_list->currentIndex(); //获取当前 modelIndex
    qDebug()<< index;
    QString data = addedModel->data(index).toString();
   if( addedModel->removeRow(index.row())) //删除当前行
   {
       addedModel->insertRow(addedModel->rowCount());
       QModelIndex index2 =addedModel->index(addedModel->rowCount()-1,0);
       addedModel->setData(index2,data,Qt::DisplayRole);
       ui->added_list->setCurrentIndex(index2);
       ui->bottom->setEnabled(false);
       ui->down->setEnabled(false);
   }
}


void UI_Plugin::on_down_clicked()
{
    QModelIndex  index;
    index=ui->added_list->currentIndex(); //获取当前 modelIndex
    if(index.row() == addedModel->rowCount()-1){
        ui->added_list->setCurrentIndex(index);
        return;
    }
    qDebug()<< index;
    QString data = addedModel->data(index).toString();
   if( addedModel->removeRow(index.row())) //删除当前行
   {
       addedModel->insertRow(index.row()+1);
       QModelIndex index2 =addedModel->index(index.row()+1,0);
       addedModel->setData(index2,data,Qt::DisplayRole);
       ui->added_list->setCurrentIndex(index2);

       ui->top->setEnabled(true);
       ui->up->setEnabled(true);
       if(index2.row() == addedModel->rowCount()-1){

           ui->bottom->setEnabled(false);
           ui->down->setEnabled(false);
       }
   }
}

void UI_Plugin::on_up_clicked()
{
    QModelIndex  index;
    index=ui->added_list->currentIndex(); //获取当前 modelIndex
    if(index.row() == 0){

        ui->added_list->setCurrentIndex(index);
        return;
    }
    qDebug()<< index;
    QString data = addedModel->data(index).toString();
   if( addedModel->removeRow(index.row())) //删除当前行
   {
       addedModel->insertRow(index.row()-1);
       QModelIndex index2 =addedModel->index(index.row()-1,0);
       addedModel->setData(index2,data,Qt::DisplayRole);
       ui->added_list->setCurrentIndex(index2);

       ui->bottom->setEnabled(true);
       ui->down->setEnabled(true);

       if(index2.row() == 0){

           ui->top->setEnabled(false);
           ui->up->setEnabled(false);
       }
   }
}

void UI_Plugin::on_top_clicked()
{
    QModelIndex  index;
    index=ui->added_list->currentIndex(); //获取当前 modelIndex
    qDebug()<< index;
    QString data = addedModel->data(index).toString();
   if( addedModel->removeRow(index.row())) //删除当前行
   {
       addedModel->insertRow(0);
       QModelIndex index2 =addedModel->index(0,0);
       addedModel->setData(index2,data,Qt::DisplayRole);
       ui->added_list->setCurrentIndex(index2);
       ui->top->setEnabled(false);
       ui->up->setEnabled(false);
   }
}


void UI_Plugin::on_added_list_pressed(const QModelIndex &index)
{
    ui->removePlugin->setEnabled(true);
    ui->up->setEnabled(true);
    ui->down->setEnabled(true);
    ui->top->setEnabled(true);
    ui->bottom->setEnabled(true);
    if(index.row() == addedModel->rowCount()-1){
        ui->bottom->setEnabled(false);
        ui->down->setEnabled(false);
    }
    if(index.row() == 0){
        ui->top->setEnabled(false);
        ui->up->setEnabled(false);
    }
}

void UI_Plugin::on_unadded_list_pressed(const QModelIndex &index)
{

    ui->addPlugin->setEnabled(true);
}

void UI_Plugin::on_unadded_list_customContextMenuRequested(const QPoint &pos)
{
    cmenu->exec(QCursor::pos());
}
