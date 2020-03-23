#include "pluginconfigure.h"
#include <QDir>
PluginConfigure::PluginConfigure(QString pluginFilePath, QString pluginAddedFileName, QString pluginUnaddedFileName)
{
    this->pluginFilePath = pluginFilePath;
    this->pluginAddedFileName = pluginAddedFileName;
    this->pluginUnaddedFileName = pluginUnaddedFileName;
}
QString PluginConfigure::getPluginFilePath()
{
    return this->pluginFilePath;
}
QString PluginConfigure::getPluginAddedFileName(){
    return this->pluginAddedFileName;
}
QString PluginConfigure::getPluginUnaddedFileName(){
    return this->pluginUnaddedFileName;
}

QString PluginConfigure::getAbsolutePluginAddedFile(){
    QDir dir(this->pluginFilePath);
    return dir.absoluteFilePath(this->pluginAddedFileName);
}
