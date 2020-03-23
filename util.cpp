#include "util.h"
#include <QDir>
#include <QDebug>

Util::Util()
{

}
int Util::createFile(QString filePath,QString fileName)
{
    QDir tempDir;
    QString currentDir = tempDir.currentPath();
    if(!tempDir.exists(filePath))
    {
        tempDir.mkpath(filePath);
    }
    QFile *tempFile = new QFile;
    tempDir.setCurrent(filePath);
    if(tempFile->exists(fileName))
    {
        qDebug()<<fileName<<QObject::tr(" already Exist");

        tempDir.setCurrent(currentDir);
        return -1;
    }
    tempFile->setFileName(fileName);
    if(!tempFile->open(QIODevice::WriteOnly|QIODevice::Text))
    {

        tempDir.setCurrent(currentDir);
        return -1;
    }
    tempFile->close();
    tempDir.setCurrent(currentDir);
    return 0;
}
