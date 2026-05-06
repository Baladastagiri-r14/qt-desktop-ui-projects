#ifndef SMART_H
#define SMART_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <QGraphicsSceneHoverEvent>
#include <QPolygonF>
class smart : public QGraphicsScene
{
    Q_OBJECT
public:
    smart(QWidget *parent);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnter(QGraphicsSceneHoverEvent *event);
    void brush();
    void check();
    void getcirclecoordinates();
    void checkmouse();
    double distance(QPointF p1,QPointF p2);
    QPointF midpoint(QPointF p1,QPointF p2);

    QPointF p1,p2,p3,p4,p5,p6,p7,p8,endpoint;
    QList<QPointF> list1,list2;
    QList<QPointF> list1dest,list2dest;
    QList<QPointF> mergedlist;
    QList<QPolygonF> polylist;
    QList<QPolygonF> newlist;
    QPolygonF insert;
    int x;
    QMap<int,QList<QPointF>> map;
    QMap<int,QList<QPolygonF>> polymap;

    QPointF upperpoint,lowerpoint,leftpoint,rightpoint,centre;

    bool hover;
    QPointF currentpoint;
    int radius;
    bool press;
    bool startcheck;
    int choice=0;

    QGraphicsEllipseItem *ellipse;
    QGraphicsEllipseItem *ellipseend;
    QGraphicsPathItem *pathupper;
    QGraphicsPathItem *pathlower;
    QGraphicsPathItem *pathextension;

    //testing
    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;
    QGraphicsLineItem *line3;
    QGraphicsLineItem *line4;

    QPainterPath *path1;
    QPainterPath *path2;
    QPainterPath *extension;

    QPolygonF poly;
    QGraphicsPolygonItem *polygon;
    QGraphicsPolygonItem *oldpolygon;
};

#endif // SMART_H
