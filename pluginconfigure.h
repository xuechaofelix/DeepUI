#ifndef PLUGINCONFIGURE_H
#define PLUGINCONFIGURE_H

#include <QString>

class PluginConfigure
{
public:
    PluginConfigure(QString pluginFilePath, QString pluginAddedFileName, QString pluginUnaddedFileName);
    QString getPluginFilePath();
    QString getPluginAddedFileName();
    QString getPluginUnaddedFileName();
    QString getAbsolutePluginAddedFile();

private:
    QString pluginFilePath;
    QString pluginAddedFileName;
    QString pluginUnaddedFileName;
};

#endif // PLUGINCONFIGURE_H
