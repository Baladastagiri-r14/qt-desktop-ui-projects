#include "mouse.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

mouse::mouse()
{

}

void mouse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
    {
        startingpoint = event->scenePos();

    }
     QGraphicsScene::mousePressEvent(event);

}

void mouse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{


    if(event->buttons() == Qt::RightButton)
    {



            deltaX  = event->scenePos().x() - startingpoint.x();
            deltaY  = event->scenePos().y() - startingpoint.y();
            deltaY = (deltaY/3072.0)*100;
            deltaX = (deltaX/3072.0)*5;


            angleInDegrees = atan2(deltaY, deltaX) * 180 / 3.141;
            qDebug()<<"angleInDegrees"<<angleInDegrees;

            
//            if(angleInDegrees >=45)
//            {
//                if(angleInDegrees<=135)
//                {
//                    vartical = true;
//                    qDebug()<<"vretical value1"<<vartical<<"horizantal value1"<<horizantal;
//                }
//                else
//                {
//                   vartical=false;
//                }

//            }

//            if(angleInDegrees>=0)
//            {
//                if(angleInDegrees<=44)
//                {
//                    horizantal= true;

//                    qDebug()<<"horizantal value1"<<horizantal<<"vretical value1"<<vartical;
//                }
//                else
//                 {
//                    horizantal=false;
//                 }
//            }
//            if(angleInDegrees >=136)
//            {
//                if(angleInDegrees <=180)
//                {
//                    horizantal= true;
//                    qDebug()<<"horizantal value2"<<horizantal<<"vretical value2"<<vartical;
//                }
//                else
//                 {
//                    horizantal=false;
//                 }

//            }





            if(angleInDegrees>=-179)
            {
                if(angleInDegrees<=-136)
                {
                    horizantal = true;

                }
                else
                 {
                    horizantal=false;
                 }
           }
            if(angleInDegrees>=-135)
            {
                if(angleInDegrees<=-45)
                {
                    vartical = true;
                }

                else
                 {
                    vartical=false;
                 }
            }
            if(angleInDegrees >=-44)
            {
                if(angleInDegrees<0)
                {
                    horizantal = true;

                }
                else
                 {
                    horizantal=false;
                 }
            }
//            qDebug()<<"--------------------"<<heigh<<deltaY;

            emit buttonclick();


    }
    QGraphicsScene::mouseMoveEvent(event);

}

void mouse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{


    heigh=deltaY+heigh;
    widh = deltaX+widh;
    qDebug()<<heigh<<deltaY<<"release"<<widh<<deltaX;


    QGraphicsScene::mouseReleaseEvent(event);

}

void mouse::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

     if(event->buttons() == Qt::RightButton)
     {
        qDebug()<<"double click";
//        heigh = 0;
//        widh = 0;
        emit doubleclick();
     }



    QGraphicsScene::mouseDoubleClickEvent(event);

}
