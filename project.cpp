#include "project.h"
#include <QDir>
#include <QDebug>
#include "util.h"


Project::Project(const QString & path, const QString & name)
{
    this->path = path;
    this->name = name;

  //  QDir dir(path);
  //  Util::createFile(dir.absolutePath(),"addedplugin.txt");
  //  Util::createFile(dir.absolutePath(),"unaddedplugin.txt");

  //  this->pcf = new PluginConfigure(dir.absolutePath(),"addedplugin.txt","unaddedplugin.txt");

}
Project::Project(const QString & name)
{
    this->path = "";
    this->name = name;
}
QVariant Project::get(int column) const
{
    if (column < 0 || column >= ELEMENT_NUMBER)
        return QVariant();
    if(column == 0){
        return this->name;
    }
    else if(column == 1){
        return this->path;
    }
    else{
        return QVariant();
    }
}
int Project::count() const
{
    return ELEMENT_NUMBER;
}

void Project::save()
{
    QString project = this->serilize();
    QDir dir(this->path);
    QFile file(dir.absoluteFilePath(this->name+".pro"));
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(project.toUtf8());
    file.close();
    emit saveProject();
}

void Project::open(QString projectFile)
{

    QFile file(projectFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    this->unserilize(QString(t));
    file.close();
}

QString Project::serilize()
{
    return this->modelFile+";"+this->formuleFile+";";
}

QString Project::getModelFileName()
{
    QFileInfo info(this->modelFile);
    return info.fileName();
}
QString Project::getFormuleFileName(){
    QFileInfo info(this->formuleFile);
    return info.fileName();
}



int Project::unserilize(const QString & project)
{
    QStringList list = project.split(";");
    if(list.size()<2) return UNSERILIZE_FAILED;
    if(list[0].compare("") != 0)
        this->setModelFile(list[0]);
    if(list[1].compare("") != 0)
        this->setFormuleFile(list[1]);
   // bool * ok = new bool;
    //int type = list[2].toInt(ok);
    //if(! *ok) return UNSERILIZE_FAILED;
    //this->setModelType(type);
    return UNSERILIZE_SUCCESS;
}

void Project::setModelFile(const QString & modelFileName)
{
    this->modelFile = modelFileName;
    this->isSetModelFile= true;
}
void Project::setFormuleFile(const QString & formuleFileName)
{
    this->formuleFile = formuleFileName;
    this->isSetFormuleFile=true;
}
QString Project::getModelFileSuffix()
{
    /*(if(this->robustnessType == PRISM_FILE){
        return ".prism";
    }
    else if(this->robustnessType == JANI_FILE){
        return ".jani";
    }
    else {
        return "";
    }*/
    return ".rlv";
}
QString Project::getFormuleFileSuffix()
{
    return ".txt";
}

QString Project::getModelFile()
{
    QDir dir(this->path);
    return dir.absoluteFilePath(this->modelFile);
}
QString Project::getFormuleFile()
{
    QDir dir(this->path);
    return dir.absoluteFilePath(this->formuleFile);
}

/*void Project::setRobustnessType(QString robustnessType)
{
    this->robustnessType = robustnessType;
    this->isSetRobustnessType = true;
}

QString Project::getRobustnessType()
{
    return this->robustnessType;
}*/

QString Project::getPath()
{
    return this->path;
}
QString Project::getName()
{
    return this->name;
}
bool Project::isValidModelFile(){
    return this->isSetModelFile;
}
bool Project::isValidFormuleFile(){
    return this->isSetFormuleFile;
}
/*bool Project::isValidRobustnessType(){
    return this->isSetRobustnessType;
}*/
//todo
QString Project::generateParametersList()
{
    if(!this->isValidModelFile()){
        return "";
    }
    if(!this->isValidFormuleFile()){
        return "";
    }

    return "--network "+this->getModelFile()+" --image "+this->getFormuleFile();
}
