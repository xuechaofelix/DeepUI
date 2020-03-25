#include "util.h"
#include <QDir>
#include <QDebug>

Util::Util()
{

}
int Util::createFile( const QString filePath, const QString fileName)
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

int Util::parseJsonFile(const QString filePath, const QString fileName, QJsonObject & result)
{
    QDir filepath(filePath);

    QFile file(filepath.absoluteFilePath(fileName));
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString value = file.readAll();
        file.close();

        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);
        if(!(parseJsonErr.error == QJsonParseError::NoError))
        {
            qDebug()<<"解析json文件错误！";
            return -1;
        }
        result = document.object();
        return 0;
}
