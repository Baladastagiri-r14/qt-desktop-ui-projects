#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>

class CustomScene : public QGraphicsScene
{
public:
    CustomScene();

    bool pressed;
    double radius;

    QPolygonF poly;
    QPointF p1,p2,p3,p4,p5,p6;
    QList<QPointF>list1,list2;

    QPainterPath *path = NULL;
    QGraphicsPathItem *item = NULL;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENE_H
