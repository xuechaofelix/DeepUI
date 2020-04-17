#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QMap>

class Node;

//! [0]
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);
//    ~GraphWidget() override;

    void itemMoved();

    void addNode(QString name);
    void addEdge(QString node1,QString node2);
    void setCenterNode(QString name);
    void clear();

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
   // void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

private:
    int timerId;
    Node *centerNode;
    QMap<QString,Node*> nodesMap;
};
//! [0]

#endif // GRAPHWIDGET_H
