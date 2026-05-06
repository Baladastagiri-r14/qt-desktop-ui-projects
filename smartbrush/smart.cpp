#include "smart.h"
#include <QDebug>
#include <QtMath>
#include <QCursor>
#include <QTimer>
#include <QtCore>
smart::smart(QWidget* parent):QGraphicsScene(parent)
{
hover=false;
radius=240;
QTimer *time=new QTimer();
connect(time,&QTimer::timeout,this,&smart::checkmouse);
time->start(100);
startcheck=false;
choice=0;
x=0;
}
int c=0;
double smart::distance(QPointF p1,QPointF p2){
    return qSqrt(qPow((p2.x()-p1.x()),2)+qPow((p2.y()-p1.y()),2));
}
QPointF smart::midpoint(QPointF p1,QPointF p2){
    return QPointF((p1.x()+p2.x())/2,(p1.y()+p2.y())/2);
}
void smart::checkmouse(){

}
void smart::getcirclecoordinates(){
    centre= QPointF((ellipse->scenePos().x()+(ellipse->boundingRect().height())/2),((ellipse->scenePos().y()+(ellipse->boundingRect().width())/2)));
    lowerpoint=QPointF((ellipse->scenePos().x()+(ellipse->boundingRect().height())/2),((ellipse->scenePos().y()+(ellipse->boundingRect().width()))));
    rightpoint=QPointF((ellipse->scenePos().x()+(ellipse->boundingRect().height())),((ellipse->scenePos().y()+(ellipse->boundingRect().width())/2)));
    upperpoint=QPointF((ellipse->scenePos().x()+(ellipse->boundingRect().height())/2),((ellipse->scenePos().y()+(ellipse->boundingRect().width())/2-120)));
    leftpoint=QPointF((ellipse->scenePos().x()+(ellipse->boundingRect().height())/2-120),((ellipse->scenePos().y()+(ellipse->boundingRect().width())/2)));

}
void smart::check()
{
 if(startcheck){
    getcirclecoordinates();
  if(polygon->collidesWithItem(ellipse)){
      ellipse->setPen(QPen(Qt::green,13,Qt::SolidLine));
      choice=1;
  }
 else{
     ellipse->setPen(QPen(Qt::red,13,Qt::SolidLine));
     choice=0;
 }

}
}


void smart::brush(){
    if(c<1){
        ellipse=new QGraphicsEllipseItem();
        ellipse->setPen(QPen(Qt::red,13,Qt::SolidLine));
        this->addItem(ellipse);

    }
  c++;
  ellipse->setRect(0,0,radius,radius);
  foreach (QGraphicsItem* item,items()) {
      QGraphicsEllipseItem* node =qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
      if(node){
          item->setFlag(QGraphicsItem::ItemIsMovable);
          item->setAcceptHoverEvents(true);
      }
  }
}

void smart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   qDebug()<<"hello";
   hover=true;
   brush();
   ellipse->setPos(event->scenePos().x(),event->scenePos().y());
   p1=event->scenePos();
   list1.append(event->scenePos());
   list2.append(event->scenePos());
   check();
   getcirclecoordinates();
   QGraphicsScene::mousePressEvent(event);
}

void smart::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   check();
   ellipse->setPos(event->scenePos().x(),event->scenePos().y());

   if(hover){
   brush();
   p2=event->scenePos();

   p3 = QPointF((p1.x()+(radius/2)*qCos(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())+qAcos(0))),(p1.y()+(radius/2)*qSin(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())+qAcos(0))));
   p4 = QPointF((p2.x()+(radius/2)*qCos(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())+qAcos(0))),(p2.y()+(radius/2)*qSin(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())+qAcos(0))));
   p5 = QPointF((p1.x()+(radius/2)*qCos(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())-qAcos(0))),(p1.y()+(radius/2)*qSin(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())-qAcos(0))));
   p6 = QPointF((p2.x()+(radius/2)*qCos(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())-qAcos(0))),(p2.y()+(radius/2)*qSin(qAtan2(p2.y()-p1.y(),p2.x()-p1.x())-qAcos(0))));

   list1.append(p3);
   list1.append(p4);
   list2.append(p5);
   list2.append(p6);

    if(choice==0){//case1

   if(!pathupper){
       pathupper=new QGraphicsPathItem();
       path1=new QPainterPath();
       pathupper->setPen(QPen(Qt::yellow,5,Qt::SolidLine));
       this->addItem(pathupper);
   }
   for(int i=0;i<list1.length();i++){
       if(i==0){
           path1->moveTo(list1.at(i));

       }
       else{
           path1->lineTo(list1.at(i));
       }
   }
   pathupper->setPath(*path1);

   if(!pathlower){
       pathlower=new QGraphicsPathItem();
       path2=new QPainterPath();
       pathlower->setPen(QPen(Qt::yellow,5,Qt::SolidLine));
       this->addItem(pathlower);
   }

   for(int i=0;i<list2.length();i++){
       if(i==0){
          path2->moveTo(list2.at(i));
     }
       else{
          path2->lineTo(list2.at(i));
       }
   }
   pathlower->setPath(*path2);
   p1=p2;
   if(list1.length()>80){
     QPointF midpointline1=midpoint(list1.at(1),list1.at(list1.length()-1));
     QPointF midpointline2=midpoint(list2.at(1),list2.at(list2.length()-1));
     double distance2=distance(list2.at(1),list2.at(list2.length()-1));
     double distance1=distance(list1.at(1),list1.at(list1.length()-1));
     double distancemid=distance(midpointline1,midpointline2);
     qDebug()<<p6.x()-p5.x();
     qDebug()<<"distance 1"<<distance1<<"distance 2"<<distance2;
     qDebug()<<qLn(distance1-distance2);
     qDebug()<<"middist"<<distancemid;
     if(qLn(distance1-distance2)<0){
        this->removeItem(pathlower);
        path1->lineTo(list1.at(1));
        pathupper->setPath(*path1);
      }
     }
   }
    if(choice==1){

    }

    QGraphicsScene::mouseMoveEvent(event);
}
}
void smart::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
   qDebug()<<"choice"<<choice;
   if(list1.length()>2 && choice==0){
       startcheck=true;
       path2->lineTo(list1.at(list1.length()-3));
       pathlower->setPath(*path2);
       for(int i=0;i<=list1.length()-3;i++){
           poly<<list2.at(i)<<list1.at(i);
        }
      polygon=new QGraphicsPolygonItem();
      polygon->setPolygon(poly);
      this->addItem(polygon);

      mergedlist=list1+list2;
      map.insert(x,mergedlist);

      polylist.append(poly);
      polymap.insert(x,polylist);
      newlist=polymap.value(x);
      insert=newlist.at(x);
      qDebug()<<"length"<<mergedlist.length();
      qDebug()<<"x"<<x;
      ++x;

      line2=new QGraphicsLineItem();
      line2->setPen(QPen(Qt::red,65));
      line2->setPos(mergedlist.at(mergedlist.length()-1));
      this->addItem(line2);

      line1=new QGraphicsLineItem();
      line1->setPen(QPen(Qt::red,65));
      line1->setPos(mergedlist.at(mergedlist.length()/2-1));
      this->addItem(line1);

//      line3=new QGraphicsLineItem();
//      line3->setPen(QPen(Qt::red,65));
//      line3->setPos(polygon->boundingRect().center());
//      this->addItem(line4);
   }
   hover=false;
   list1.clear();
   list2.clear();
   path1=NULL;
   path2=NULL;
   pathlower=NULL;
   pathupper=NULL;
   poly.clear();//

   QGraphicsScene::mouseReleaseEvent(event);
}

void smart::hoverEnter(QGraphicsSceneHoverEvent *event)
{
    hover=true;
}

