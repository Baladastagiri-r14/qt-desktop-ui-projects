#include "customscene.h"

#include <QtGui>
#include <QtCore>
#include <QtMath>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

CustomScene::CustomScene()
{
    radius = 30;
    pressed = false;
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    p1 = event->scenePos();

    QGraphicsScene::mousePressEvent(event);
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    p2 = event->scenePos();

    p3 = QPointF((p1.x()+radius*qCos(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())+qAcos(0))),(p1.y()+radius*qSin(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())+qAcos(0))));
    p4 = QPointF((p2.x()+radius*qCos(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())+qAcos(0))),(p2.y()+radius*qSin(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())+qAcos(0))));

    p5 = QPointF((p1.x()+radius*qCos(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())-qAcos(0))),(p1.y()+radius*qSin(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())-qAcos(0))));
    p6 = QPointF((p2.x()+radius*qCos(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())-qAcos(0))),(p2.y()+radius*qSin(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())-qAcos(0))));

    list1.append(p3);
    list1.append(p4);

    list2.append(p5);
    list2.append(p6);

    poly.clear();
    path = NULL;

    for(int i=0;i<list1.length();i++){
        if(i == 0)
            poly<<list2.at(i);
        else
            poly<<list1.at(i);
    }
    for(int j=list2.length()-1;j>=0;j--){
        if(j == list2.length()-1)
            poly<<list1.at(j);
        else
            poly<<list2.at(j);
    }

    path = new QPainterPath;
    path->addPolygon(poly);

    if(!item){
        item = new QGraphicsPathItem;
        addItem(item);
        item->setPen(QPen(Qt::cyan,4));
    }
    item->setPath(*path);

    p1 = p2;

    QGraphicsScene::mouseMoveEvent(event);
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;

    list1.clear();
    list2.clear();
    poly.clear();

    path = NULL;
    item = NULL;

    QGraphicsScene::mouseReleaseEvent(event);
}

