#include "backend.h"
#include <QFileInfo>
#include <QDebug>
BackEnd::BackEnd(const QString excuteFileName)
{
    this->excuteFile = excuteFileName;
    QFile file(this->excuteFile);
    cmd = new QProcess(this);
    connect(cmd , SIGNAL(readyReadStandardOutput()) , this , SLOT(on_readoutput()));
    connect(cmd , SIGNAL(readyReadStandardError()) , this ,SLOT(on_readerror()));
    //cmd->setWorkingDirectory("~");
    //cmd->start("bash");
    #if defined(Q_OS_WIN32)
    cmd->start("cmd.exe");
    #elif defined(Q_OS_LINUX)
    file.setPermissions(QFile::ExeUser);
    cmd->start("bash");
    #endif

    cmd->waitForStarted();


}
BackEnd::~BackEnd(){
    if(cmd){
        cmd->close();
        cmd->waitForFinished();
    }
}
bool BackEnd::getIsBusy(){
    return this->isBusy;
}
int BackEnd::setCurrentModel(const QString modelFile){
    QFileInfo fi(modelFile);
    if(!fi.isFile()) return IS_NOT_FILE;
    this->currentModel = modelFile;
    return RUN_SUCCESS;
}
int BackEnd::setCurrentFormule(const QString formuleFile){
    QFileInfo fi(formuleFile);
    if(!fi.isFile()) return IS_NOT_FILE;
    this->currentFormule = formuleFile;
    return RUN_SUCCESS;
}
void BackEnd::setCurrentParametersList(const QString parametersList){

    this->currentParametersList = parametersList;
}


void BackEnd::on_readoutput()
{
   // QString result =QString(cmd->readAllStandardOutput().data());
    emit sendOut(cmd->readAllStandardOutput().data());
    //out.append(cmd->readAllStandardOutput().data());
    //qDebug() << result;
    //this->isBusy = false;
}

void BackEnd::on_readerror()
{
    //QString result = QString(cmd->readAllStandardError().data());
    emit sendOut(cmd->readAllStandardError().data());
    //qDebug() << result;
    //out.append(cmd->readAllStandardError().data());
    //this->isBusy = false;
}
int BackEnd::run(){
    if(this->isBusy){
        return BUSY_STATUS;
    }

    this->isBusy = true;

    QString command = this->excuteFile +" " +
                      this->currentParametersList
            ;

    qDebug() << command;
    cmd->write("java --version\n");
    cmd->write((command).toLocal8Bit() + '\n');

    //cmd->execute(command);
    this->isBusy = false;
    return RUN_SUCCESS;
}
