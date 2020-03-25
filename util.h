#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

class Util
{
public:
    Util();
    static int createFile(const QString filePath, const QString fileName);
    static int parseJsonFile(const QString filePath, const QString fileName, QJsonObject & result);
};

#endif // UTIL_H
