#ifndef BACKEND_H
#define BACKEND_H

#include<QString>
#include<QProcess>

#define RUN_SUCCESS 0
#define BUSY_STATUS -1
#define IS_NOT_FILE -2

class BackEnd: public QObject
{
    Q_OBJECT
private:
    QString excuteFile;
    bool isBusy = false;
    QString currentModel;
    QString currentFormule;
    QString currentParametersList;
    QString out;
    QProcess * cmd;
public:

    BackEnd(const QString excuteFileName);
    bool getIsBusy();
    QString getOutput();
    int setCurrentModel(const QString modelFile);
    int setCurrentFormule(const QString formuleFile);
    void setCurrentParametersList(const QString parametersList);

    int run();

    ~BackEnd();
signals:
    void sendOut(char * text);

private slots:
    void on_readoutput();
    void on_readerror();

};

#endif // BACKEND_H
