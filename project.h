#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QVariant>

//#include "pluginconfigure.h"

#define ROBUSTNESS_INF 0
#define ROBUSTNESS_BRI 1
#define ROBUSTNESS_CUS 2

#define UNSERILIZE_FAILED -1
#define UNSERILIZE_SUCCESS 0


#define ELEMENT_NUMBER 2


class Project: public QObject
{
    Q_OBJECT
private:
    QString path;
    QString modelFile;
    QString formuleFile;
   // QString robustnessType = ROBUSTNESS_TYPE_LINFBALL;
    QString name;

    bool isSetModelFile = false;
    bool isSetFormuleFile = false;
   // bool isSetRobustnessType = false;

    QString serilize();
    int unserilize(const QString & project);

    //PluginConfigure * pcf;

signals:
    void closeFile();
    void saveProject();

public:
    Project(const QString & path, const QString & name);
    Project( const QString & name);
    void setModelFile(const QString & modelFileName);
    void setFormuleFile(const QString & formuleFileName);
   // void setRobustnessType(QString robustnessType);

    QString getModelFileSuffix();
    QString getFormuleFileSuffix();

    //QString getRobustnessType();
    QString getModelFile();
    QString getFormuleFile();
    QString getModelFileName();
    QString getFormuleFileName();
    QString getPath();
    QString getName();
    QString generateParametersList();

    bool isValidModelFile();
    bool isValidFormuleFile();
    //bool isValidRobustnessType();

    void save();
    void open(QString projectFile);
    QVariant get(int column) const;
    int count() const;

};

#endif // PROJECT_H
