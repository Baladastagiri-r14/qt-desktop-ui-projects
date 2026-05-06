#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include<QGraphicsEllipseItem>
#include<QGraphicsPathItem>
#include <QPainter>


struct Drawing
{
    QString type;
    QPointF pos;
    QList<QPointF> pointsList;
    QList<QPointF> pointsList1;
    QList<QPointF> pointsListTemp;
    QList<double> pointListD;
    QRectF rect1;
    QString tag;
    QPointF posChange;

    int start;
    int stop;
    bool insideCircle=false;
};

struct returnList
{
    QList<Drawing*> drawingList;
    int n;
};


class CustomScene:public QGraphicsScene
{
     Q_OBJECT
public:
    CustomScene();

    enum Mode {NoMode,Brush,Freehand};
    ~CustomScene();



    Drawing *myDrawingA=NULL;
    double thresholdBrush=INFINITY;
    double thresholdBrushPrev=INFINITY;

    void smoothOut(const float& factor);




    void setMode(CustomScene::Mode mode);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:


    QPointF origPoint;

    bool validPoint=false;

    QGraphicsEllipseItem* circleBrush=NULL;

    double brushRadius;

    int circleStartIndex;
    int circleStopIndex;

    unsigned int brushPointCount=360;



    QGraphicsPathItem* path=NULL;
    QPainterPath *paintPath=NULL;

    const  float PI= 3.14159F;

    QPen drawPen;

    float pixelPitch;

    int sceneMode;

    QList<QPointF> pointListBrush;



public slots:

    void setpixelPitch(float realSize);

signals:



};

#endif
