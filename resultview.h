#ifndef RESULTVIEW_H
#define RESULTVIEW_H

#include <QWidget>
#include "comparerelation.h"
#include <QJsonObject>

namespace Ui {
class ResultView;
}

class ResultView : public QWidget
{
    Q_OBJECT

public:
    explicit ResultView(QWidget *parent = nullptr);
    ~ResultView();
    void parsingJsonFile(QString jsonFile);
    void showCompareRelation();
public slots:
    void removeSubTab(int index);

signals:
    void updateNetworkNodeStatus(QJsonObject obj);
private:
    Ui::ResultView *ui;

    CompareRelation * resultGraph = nullptr;
};

#endif // RESULTVIEW_H
