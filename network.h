#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>
#include "networklayer.h"

namespace Ui {
class Network;
}

class Network : public QWidget
{
    Q_OBJECT

public:
    explicit Network(QWidget *parent = nullptr);
    ~Network();
    int addLayer(QString name, QString type, int flag=15, QStringList * inputName = nullptr, QStringList * outputName = nullptr);



    void setWeight(int layerIndex, int row, int column, QString value);
    void setBias(int layerIndex, int index, QString value);
    void setLayerName(int index, QString name);
    void setLayerDescription(int index, QString description);

    void saveNetwork();

    void clear();

    bool isLoaded();

    int layerIndexOf(QString layerName);

    void setBoundOfNode(int index, QString nodeName, QString inf, QString sup);

    void reload();
    int updateUI(QList<NetworkLayerData *> * layers);

public slots:
    //void loadNetworkfile(QString filePath, QString fileName);
    void on_IsValueChanged();

private:
    Ui::Network *ui;

    QString filePath = "";
    QString fileName = "";
    QList<NetworkLayer *> * layers = new QList<NetworkLayer *>();
    bool isLoadedFlag = false;
    bool isValueChanged = false;
};

#endif // NETWORK_H
