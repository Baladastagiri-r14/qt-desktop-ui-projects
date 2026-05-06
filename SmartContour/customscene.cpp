#include "customscene.h"
bool pressed;

#include <QDebug>
#include <QApplication>

#define PI 3.14159

CustomScene::CustomScene()
{

    drawPen=QPen(Qt::blue, 3, Qt::SolidLine);
    circleBrush = 0;
    path=0;
    paintPath=0;
    pixelPitch=1.0;

}
CustomScene::~CustomScene()
{

}


void CustomScene::setpixelPitch(float realSize)
{
    pixelPitch = realSize;
}


void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug()<<"mouse pressed";

    if (event->button() != Qt::LeftButton)
        return;

    qDebug()<<"JJ"<<event->scenePos();

    if (sceneMode!=0){
        origPoint = event->scenePos();

        pressed   = true;
    }

    QGraphicsScene::mousePressEvent(event);

}


void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if(!pressed)
      return;

//    if(m_dragging) {
//        myDrawingA->pointsList[m_selectedPoint] = event->pos();
//    }
//    update();

    switch (sceneMode) {
    case Freehand:
    {
     if(!path)
     {

         path=new QGraphicsPathItem;
         path->setFlag(QGraphicsItem::ItemIsMovable,false);
         path->setPen(drawPen);
         path->setPos(origPoint);

         this->addItem(path);

         paintPath = new QPainterPath;

         myDrawingA = new Drawing;
         myDrawingA->pos=origPoint;
         myDrawingA->type="freehand";

     }

     myDrawingA->pointsList.append(event->scenePos());

     paintPath->lineTo(event->scenePos().x()-origPoint.x(),event->scenePos().y()-origPoint.y());

     path->setPath(*paintPath);


     break;
    }
    case Brush:
        {

        break;
        }


    default:
        break;
    }

    QGraphicsScene::mouseMoveEvent(event);

}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!pressed)
      return;


    if(event->scenePos()==origPoint)
    {
        QGraphicsScene::mouseReleaseEvent(event);
        return;
    }

    switch (sceneMode) {
    case Freehand:
    {

        int len=myDrawingA->pointsList.length()-1;

        double yinterp = origPoint.y()-myDrawingA->pointsList.at(len).y();

        double xinterp = origPoint.x()-myDrawingA->pointsList.at(len).x();

        qDebug()<<"yinterp;"<<yinterp<<origPoint.y()<<myDrawingA->pointsList.at(len).y();

        double yratio = yinterp/(std::abs(yinterp));

        double xratio = xinterp/(std::abs(yinterp));


        qDebug()<<"xratio"<<xratio<<yratio<<int(std::abs(yinterp));

        for(int j=1;j<=int(std::abs(yinterp));j++)
        {
            myDrawingA->pointsList.append(QPointF(j*xratio+myDrawingA->pointsList.at(len).x(),j*yratio+myDrawingA->pointsList.at(len).y()));
          //  paintPath->lineTo(myDrawingA->pointsList.at(myDrawingA->pointsList.length()-1).x(),0);
        }

        myDrawingA->pointsList.append(origPoint);

        paintPath->lineTo(0,0);

        path->setPath(*paintPath);


        this->setMode(NoMode);


        break;
    }
    case Brush:
    {
        qDebug()<<"entered brush";

        if(!circleBrush->isUnderMouse())
            return;
        myDrawingA->start = 0;
        myDrawingA->stop = 0;
        thresholdBrush=INFINITY;
        thresholdBrushPrev=INFINITY;
        /*added*/
        if(!myDrawingA->pointListD.isEmpty())
            myDrawingA->pointListD.clear();
            validPoint=false;

        /*added*/

        qDebug()<<"centere entered brush";
        //Circle Updated Points while moving it
        for(int i=0;i<brushPointCount;i++){
            pointListBrush.replace(i,QPointF(pointListBrush.at(i).x()+event->scenePos().x()-origPoint.x(),pointListBrush.at(i).y()+event->scenePos().y()-origPoint.y()));

        }
        //Circle Updated Points while moving it

         QPointF centere;

         centere=circleBrush->sceneBoundingRect().center();


        qDebug()<<centere;

        //Finding the distance of contour points from the center of the updated circle(moved item)
        for(int i=0;i<myDrawingA->pointsList.length();i++){

                myDrawingA->pointListD.append(sqrtf((myDrawingA->pointsList.at(i).x()-centere.x())*(myDrawingA->pointsList.at(i).x()-centere.x())
                                                    +(myDrawingA->pointsList.at(i).y()-centere.y())*(myDrawingA->pointsList.at(i).y()-centere.y())));


        }
        //Finding the distance of contour points from the center of the updated circle(moved item)



        qDebug()<<"length"<<myDrawingA->pointListD.length()<<myDrawingA->pointsList.length();

 //qDebug()<<"pointlistd"<< myDrawingA->pointListD;


 //We need to find the start and end point of circle which are inside the freehand contour

        for(int i=1;i<myDrawingA->pointListD.length();i++)
        {
             //Since radius of the circle is 50 thats why if distance of the contour points from the center is less than radius of the circle then contour points lies inside the circle
                if(myDrawingA->pointListD.at(i)<=50  && myDrawingA->insideCircle==false)
                {

                   //We got first point from contour inside drawn circle
                   myDrawingA->insideCircle=true;

                   //if(i>0)
                   myDrawingA->start=i-1-5;


                   if( myDrawingA->start==0)
                   {
                     myDrawingA->insideCircle=false;
                     break;
                   }
                  // else
                  // myDrawingA->start=0;


                   qDebug()<<"inside the circle";
                   validPoint=true;

                   for(int j=0;j<brushPointCount;j++) //BrushPointCount is number of points of circle
                   {
                        //Calculating Distance of Contour point from updated circle points
                       thresholdBrush=sqrtf((myDrawingA->pointsList.at(i).x()-pointListBrush.at(j).x())*(myDrawingA->pointsList.at(i).x()-pointListBrush.at(j).x())
                                            +(myDrawingA->pointsList.at(i).y()-pointListBrush.at(j).y())*(myDrawingA->pointsList.at(i).y()-pointListBrush.at(j).y()));

                       if(thresholdBrush<thresholdBrushPrev)
                       {
                           circleStartIndex=j; //Start Point of the circle which is nearer to the contour Point
                           thresholdBrushPrev=thresholdBrush;
                         //  qDebug()<<"1st"<<thresholdBrushPrev;

                       }


                   }

                   qDebug()<<"circleStartIndex"<<circleStartIndex;


                }
                thresholdBrush=INFINITY;
                thresholdBrushPrev=INFINITY;
                if(myDrawingA->pointListD.at(i)>50&&myDrawingA->insideCircle==true)
                {

                   myDrawingA->insideCircle=false;
                   myDrawingA->stop=i+5;

                   //tAKING the second corner of the circle
                   qDebug()<<"outside the circle";
                   validPoint=true;

                   for(int j=0;j<brushPointCount;j++)
                   {

                       thresholdBrush=sqrtf((myDrawingA->pointsList.at(i-1).x()-pointListBrush.at(j).x())*(myDrawingA->pointsList.at(i-1).x()-pointListBrush.at(j).x())
                                            +(myDrawingA->pointsList.at(i-1).y()-pointListBrush.at(j).y())*(myDrawingA->pointsList.at(i-1).y()-pointListBrush.at(j).y()));

                       if(thresholdBrush<thresholdBrushPrev)
                       {
                           circleStopIndex=j;  //End Point of the circle which is nearer to the contour Point
                           thresholdBrushPrev=thresholdBrush;
                             // qDebug()<<"2nd"<<thresholdBrushPrev;
                       }



                   }

                   qDebug()<<"circleStopIndex"<<circleStopIndex;

                   break;

                }


        }


       if( myDrawingA->start==0)
       {
        for(int i=myDrawingA->pointListD.length()/2;i>=0;i--)
        {
            if(myDrawingA->pointListD.at(i)<=50  && myDrawingA->insideCircle==false)
            {

                qDebug()<<"Entering12121212"<<i+1;
               //We got first point from contour inside drawn circle
               myDrawingA->insideCircle=true;
               myDrawingA->start=i+1;

               validPoint=true;


               for(int j=0;j<brushPointCount;j++) //BrushPointCount is number of points of circle
               {
                    //Calculating Distance of Contour point from updated circle points
                   thresholdBrush=sqrtf((myDrawingA->pointsList.at(i).x()-pointListBrush.at(j).x())*(myDrawingA->pointsList.at(i).x()-pointListBrush.at(j).x())
                                        +(myDrawingA->pointsList.at(i).y()-pointListBrush.at(j).y())*(myDrawingA->pointsList.at(i).y()-pointListBrush.at(j).y()));

                   if(thresholdBrush<thresholdBrushPrev)
                   {
                       circleStartIndex=j; //Start Point of the circle which is nearer to the contour Point
                       thresholdBrushPrev=thresholdBrush;
                     //  qDebug()<<"1st"<<thresholdBrushPrev;

                   }


               }
            }
        }

        thresholdBrush=INFINITY;
        thresholdBrushPrev=INFINITY;

        for(int i=myDrawingA->pointListD.length()-1;i>=myDrawingA->pointListD.length()/2+1;i--)
        {
            if(myDrawingA->pointListD.at(i)>50  && myDrawingA->insideCircle==true)
            {

               //We got first point from contour inside drawn circle
               myDrawingA->insideCircle=false;
               myDrawingA->stop=i;

               qDebug()<<"Entering12121212"<<i;

               validPoint=true;


               for(int j=0;j<brushPointCount;j++) //BrushPointCount is number of points of circle
               {
                    //Calculating Distance of Contour point from updated circle points
                   thresholdBrush=sqrtf((myDrawingA->pointsList.at(i).x()-pointListBrush.at(j).x())*(myDrawingA->pointsList.at(i).x()-pointListBrush.at(j).x())
                                        +(myDrawingA->pointsList.at(i).y()-pointListBrush.at(j).y())*(myDrawingA->pointsList.at(i).y()-pointListBrush.at(j).y()));

                   if(thresholdBrush<thresholdBrushPrev)
                   {
                       circleStopIndex=j; //Start Point of the circle which is nearer to the contour Point
                       thresholdBrushPrev=thresholdBrush;
                     //  qDebug()<<"1st"<<thresholdBrushPrev;

                   }


               }
               break;
            }
        }

            QList <QPointF> tempPointList;


            int k=myDrawingA->pointsList.length()-1;
            qDebug()<<"Points "<<myDrawingA->start;
            for(int j=0;j<myDrawingA->pointsList.length();j++)
            {
               if(myDrawingA->start>=j)
               {
               tempPointList.insert(j,myDrawingA->pointsList.at(myDrawingA->start-j));
               }
               else
               {
               tempPointList.insert(j,myDrawingA->pointsList.at(k));
               k--;
               }
            }

            qDebug()<<"hello "<<myDrawingA->pointsList.at(myDrawingA->start+1)<<myDrawingA->pointsList.at(myDrawingA->start);
           // tempPointList.insert(tempPointList.length(),myDrawingA->pointsList.at(k));
            qDebug()<<"Points "<<k<<tempPointList.at(0)<<tempPointList.at(tempPointList.length()-1)<<tempPointList.length()<<myDrawingA->pointsList.length();


            for(int j=0;j<myDrawingA->pointsList.length();j++)
            {
                myDrawingA->pointsList.replace(j,tempPointList.at(j));
            }


       //     qDebug()<<"absoultevalue "<<niter<<kx<<ky<<kiter<<kx1<<ky1;
            myDrawingA->stop = myDrawingA->pointsList.length()-1-myDrawingA->stop+2+myDrawingA->start;

              myDrawingA->pointsList.append(QPointF(tempPointList.at(0).x(),tempPointList.at(0).y()));
            qDebug()<<"myDrawingAPoints "<<myDrawingA->pointsList.at(0)<<myDrawingA->pointsList.at(myDrawingA->pointsList.length()-1);
            qDebug()<<"myDrawingA->pointsList.length()"<<myDrawingA->pointsList.length()<<myDrawingA->stop<<myDrawingA->start;

            myDrawingA->start=0;

       }


qDebug()<<"start"<< myDrawingA->start<<circleStartIndex;//Start Point of Contour which is one point before contour is inside the circle
qDebug()<<"stop"<< myDrawingA->stop<<circleStopIndex;//End Point of Contour which is one point after contour was inside the circle


        if(validPoint==false)
            break;

        //4 Points are required to form a spline curve//
        //Finding the inner points of Spline (2nd and 3rd)
        QPointF curve1,curve2,curve3,curve4;
        int sector1,sector2;



        if(circleStopIndex>circleStartIndex)
        {
//            circleStartIndex=20+circleStartIndex;
//            circleStopIndex=circleStopIndex-20;
            if((circleStopIndex-circleStartIndex)>180)
            {
                int gIndex = circleStartIndex+360;
                sector1 = circleStartIndex-(gIndex-circleStopIndex)/4+360;                             //Circle is having 360 points here

                curve2 = pointListBrush.at(std::fmodf(sector1,360.0));    //This equation will change if number of circle points are changed
                sector2 = circleStopIndex+(gIndex-circleStopIndex)/4;
                curve3 = pointListBrush.at(std::fmodf(sector2,360.0));
                qDebug()<<"Sector1"<<sector1<<sector2<<gIndex<<circleStartIndex<<circleStopIndex<<curve2<<curve3;
            }
            else
            {
            sector1 = (circleStopIndex-circleStartIndex)/4+circleStartIndex;                             //Circle is having 360 points here
            curve2 = pointListBrush.at(std::fmodf(sector1,360.0));    //This equation will change if number of circle points are changed
            sector2 = (3*(circleStopIndex-circleStartIndex)/4)+circleStartIndex;
            curve3 = pointListBrush.at(std::fmodf(sector2,360.0));
            }

           //curve1
            qDebug()<<"curves1"<<curve2<<curve3<<sector1<<sector2;

        }

        else if(circleStartIndex>circleStopIndex)
        {
//            circleStartIndex=circleStartIndex-50;
//            circleStopIndex=circleStopIndex+50;
            if((circleStartIndex-circleStopIndex)>180)
            {
                int gIndex = circleStopIndex+360;
                sector1 = circleStopIndex-(gIndex-circleStartIndex)/4+360;                             //Circle is having 360 points here
                curve2 = pointListBrush.at(std::fmodf(sector1,360.0));    //This equation will change if number of circle points are changed
                sector2 = circleStartIndex+(gIndex-circleStartIndex)/4;
                curve3 = pointListBrush.at(std::fmodf(sector2,360.0));
                qDebug()<<"Sector1----"<<sector1<<sector2<<gIndex<<circleStartIndex<<circleStopIndex<<curve2<<curve3;
            }
            else
            {
            sector1 = (circleStartIndex-circleStopIndex)/4+circleStopIndex;                             //Circle is having 360 points here
            curve2 = pointListBrush.at(std::fmodf(sector1,360.0));    //This equation will change if number of circle points are changed
            sector2 = (3*(circleStartIndex-circleStopIndex))/4+circleStopIndex;
            curve3 = pointListBrush.at(std::fmodf(sector2,360.0));
            }

           qDebug()<<"curves2"<<curve2<<curve3<<sector1<<sector2;
        }

  //Calculating angle of Sector formed by two intersecting points of circle with contour

      int curveIndex1,curveIndex2;

      //  int curve1Index;

    if(myDrawingA->start!=myDrawingA->stop )
    {
        for(int i=myDrawingA->start;i<myDrawingA->stop-1;i++)
        {

//            qDebug()<<"delete";

            myDrawingA->pointsList.removeAt(myDrawingA->start+1);

        }

    qDebug()<<myDrawingA->pointsList.length();

        int k=0,m=0;


        if((circleStopIndex>circleStartIndex)&&abs(circleStopIndex-circleStartIndex)<pointListBrush.length()/2&&((pointListBrush.length()-circleStopIndex)<(pointListBrush.length()-circleStartIndex)))
        {
            qDebug()<<"Entering1";
            for(int i=0;i<(circleStopIndex-circleStartIndex);i++)
            {

                if(circleStartIndex+i==sector1)
                {
                    curveIndex1=myDrawingA->start+1+i;
//                    qDebug()<<"Entering1--"<<curveIndex1;
                }
                if(circleStartIndex+i==sector2)
                {
                    curveIndex2=myDrawingA->start+1+i;
//                    qDebug()<<"Entering1------"<<curveIndex2;
                }


//                myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(circleStartIndex+i)+pointListBrush.at(circleStartIndex+i-1)+pointListBrush.at(circleStartIndex+i+1))/3);
                myDrawingA->pointsList1.insert(myDrawingA->start+1+i,pointListBrush.at(circleStartIndex+i));

            }

        }


        else if((circleStopIndex>circleStartIndex)&&abs(circleStopIndex-circleStartIndex)>=pointListBrush.length()/2&&((pointListBrush.length()-circleStopIndex)<(pointListBrush.length()-circleStartIndex))){

            //Then remove the contour points which were inside the circle and replace with the overlapping circle points

            k=0;

            qDebug()<<"Entering2";
            //If more than half part of circle is inside the contour then contour should take the outer region of circle
            for(int i=0;i<pointListBrush.length()-abs(circleStopIndex-circleStartIndex);i++){



                if(circleStartIndex-i==sector1)
                    curveIndex1=myDrawingA->start+1+i;
                if(circleStartIndex-i==sector2)
                    curveIndex2=myDrawingA->start+1+i;

                if(i<(circleStartIndex+1))
                {
//                    qDebug()<<"Entering2--";
//                    myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(circleStartIndex-i)+pointListBrush.at(circleStartIndex-i+1)+pointListBrush.at(circleStartIndex-i-1))/3);
                     myDrawingA->pointsList.insert(myDrawingA->start+1+i,pointListBrush.at(circleStartIndex-i));
                }
                else{
//                    qDebug()<<"Entering2-------";
//                    myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(pointListBrush.length()-k-1)+pointListBrush.at(pointListBrush.length()-k)+pointListBrush.at(pointListBrush.length()-k-2))/3);
                    myDrawingA->pointsList.insert(myDrawingA->start+1+i,pointListBrush.at(pointListBrush.length()-k-1));

                    if(pointListBrush.length()-k-1==sector1)
                        curveIndex1=myDrawingA->start+1+i;
                    if(pointListBrush.length()-k-1==sector2)
                        curveIndex2=myDrawingA->start+1+i;

                    k++;
                }

            }

        }


        else if((circleStartIndex>circleStopIndex)&&abs(circleStopIndex-circleStartIndex)<pointListBrush.length()/2&&((pointListBrush.length()-circleStopIndex)>(pointListBrush.length()-circleStartIndex)))
        {

            qDebug()<<"Entering3";
            for(int i=0;i<(circleStartIndex-circleStopIndex);i++){

                if(circleStartIndex-i==sector1)
                {
                    curveIndex1=myDrawingA->start+1+i;
//                    qDebug()<<"Entering1--"<<curveIndex1;
                }
                if(circleStartIndex-i==sector2)
                {
                    curveIndex2=myDrawingA->start+1+i;
//                    qDebug()<<"Entering1------"<<curveIndex2;
                }


//                 qDebug()<<"Entering3----";
//                myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(circleStartIndex-i)+pointListBrush.at(circleStartIndex-i+1)+pointListBrush.at(circleStartIndex-i-1))/3);
                myDrawingA->pointsList.insert(myDrawingA->start+1+i,pointListBrush.at(circleStartIndex-i));

            }

        }


       else if((circleStopIndex>circleStartIndex)&&abs(circleStopIndex-circleStartIndex)>=pointListBrush.length()/2&&((pointListBrush.length()-circleStopIndex)<(pointListBrush.length()-circleStartIndex))){

            k=0;
            qDebug()<<"Entering4";
            for(int i=0;i<pointListBrush.length()-abs(circleStopIndex-circleStartIndex);i++){

                if(i<(circleStartIndex+1))
                {
//                    qDebug()<<"Entering4--";
//                    myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(circleStartIndex-i)+pointListBrush.at(circleStartIndex-i+1)+pointListBrush.at(circleStartIndex-i-1))/3);
                    myDrawingA->pointsList.insert(myDrawingA->start+1+i,pointListBrush.at(circleStartIndex-i));
                }
                else{
                    k++;
//                    qDebug()<<"Entering4-----";
//                    myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(pointListBrush.length()-k-1)+pointListBrush.at(pointListBrush.length()-k)+pointListBrush.at(pointListBrush.length()-k-2))/3);
                    myDrawingA->pointsList.insert(myDrawingA->start+1+i,pointListBrush.at(pointListBrush.length()-k-1));

                }

            }

        }



        //Implemented already above
        else if((circleStopIndex<circleStartIndex)&&abs(circleStartIndex-circleStopIndex)<pointListBrush.length()/2&&((pointListBrush.length()-circleStopIndex)<(pointListBrush.length()-circleStartIndex)))
        {
            qDebug()<<"Entering5";
            for(int i=0;i<(circleStartIndex-circleStopIndex);i++){

//                myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(circleStartIndex-i)+pointListBrush.at(circleStartIndex-i+1)+pointListBrush.at(circleStartIndex-i-1))/3);
                myDrawingA->pointsList.insert(myDrawingA->start+1+i,pointListBrush.at(circleStartIndex-i));
            }

        }

       else if((circleStopIndex<circleStartIndex)&&abs(circleStartIndex-circleStopIndex)>=pointListBrush.length()/2&&((pointListBrush.length()-circleStopIndex)>(pointListBrush.length()-circleStartIndex))){


            m=0;
            qDebug()<<"Entering6";
            for(int i=0;i<pointListBrush.length()-abs(circleStopIndex-circleStartIndex);i++){

                if(circleStartIndex+i==sector1)
                    curveIndex1=myDrawingA->start+1+i;
                if(circleStartIndex+i==sector2)
                    curveIndex2=myDrawingA->start+1+i;

                if(i<(pointListBrush.length()-circleStartIndex))
                {
//                    qDebug()<<"Entering6--";
//                    myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(circleStartIndex+i)+pointListBrush.at(circleStartIndex+i+1)+pointListBrush.at(circleStartIndex+i-1))/3);
                    myDrawingA->pointsList.insert(myDrawingA->start+1+i,pointListBrush.at(circleStartIndex+i));
                }
                else{
//                    qDebug()<<"Entering6-------";
                    m++;
//                    myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(m)+pointListBrush.at(m+1)+pointListBrush.at(m-1))/3);
                    myDrawingA->pointsList.insert(myDrawingA->start+1+i,pointListBrush.at(m));

                    if(m==sector1)
                        curveIndex1=myDrawingA->start+1+i;
                    if(m==sector2)
                        curveIndex2=myDrawingA->start+1+i;

                }

            }

        }


       else if((circleStartIndex<circleStopIndex)&&abs(circleStopIndex-circleStartIndex)<pointListBrush.length()/2&&((pointListBrush.length()-circleStartIndex)>(pointListBrush.length()-circleStopIndex)))
        {
//            qDebug()<<"Entering7---";
            for(int i=0;i<(circleStopIndex-circleStartIndex);i++){

//                myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(circleStartIndex+i)+pointListBrush.at(circleStartIndex+i+1)+pointListBrush.at(circleStartIndex+i-1))/3);
                myDrawingA->pointsList.insert(myDrawingA->start+1+i,pointListBrush.at(circleStartIndex+i));

            }

        }

       else if((circleStartIndex<circleStopIndex)&&abs(circleStopIndex-circleStartIndex)>=pointListBrush.length()/2&&((pointListBrush.length()-circleStopIndex)<(pointListBrush.length()-circleStartIndex))){


            m=0;
            qDebug()<<"Entering8";
            for(int i=0;i<pointListBrush.length()-abs(circleStopIndex-circleStartIndex);i++){

                if(i<(circleStartIndex))
                {
//                    qDebug()<<"Entering8--";
//                    myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(circleStartIndex-i)+pointListBrush.at(circleStartIndex-i+1)+pointListBrush.at(circleStartIndex-i-1))/3);
                    myDrawingA->pointsList.insert(myDrawingA->start+1+i,pointListBrush.at(circleStartIndex-i));
                }
                else{
                    m++;
//                    qDebug()<<"Entering8------";
//                    myDrawingA->pointsList.insert((myDrawingA->start+i+myDrawingA->start+1+i+myDrawingA->start+2+i)/3,(pointListBrush.at(pointListBrush.length()-m)+pointListBrush.at(pointListBrush.length()-m+1)+pointListBrush.at(pointListBrush.length()-m-1))/3);
                    myDrawingA->pointsList.insert(myDrawingA->start+1+i,pointListBrush.at(pointListBrush.length()-m));

                }

            }

        }


    }

      //Implemented already above


    qDebug()<<"PointListSize"<<myDrawingA->pointsList.length();

//        QGraphicsPathItem* path=new QGraphicsPathItem();

        if(path)
            delete path;

        path=new QGraphicsPathItem();


       // qDebug()<<"ListPointList "<<myDrawingA->pointsList;

        QPainterPath *paintPath=new QPainterPath;

        paintPath->moveTo(myDrawingA->pointsList.at(0));

//        //Finding the Slope of curve
        double Slope1,Slope2,intercept1,intercept2,constA,constB,constC;
        if(circleStopIndex>circleStartIndex)
        {
            if(myDrawingA->stop<=(myDrawingA->pointsList.length()-1-5))
            {
                qDebug()<<"Smooth--- ";
//                Slope1 = ((curve2.y()-myDrawingA->pointsList.at(myDrawingA->start-5).y())/(curve2.x()-myDrawingA->pointsList.at(myDrawingA->start-5).y()));
//                intercept1 = curve2.y()-Slope1*curve2.x();
                QPointF temp1,temp2;
                temp1 = QPointF(myDrawingA->pointsList.at(myDrawingA->stop+5).x(),myDrawingA->pointsList.at(myDrawingA->stop+5).y());
                temp2 = QPointF(myDrawingA->pointsList.at(myDrawingA->stop).x(),myDrawingA->pointsList.at(myDrawingA->stop).y());

                qDebug()<<"temp1--";
//                constA*((curve2.x()*curve2.x())-(temp1.x()*temp1.x()))+constB*(curve2.x()-temp1.x())=curve2.y()-temp1.y();
//                constA*((curve2.x()*curve2.x())-(temp2.x()*temp2.x()))+constB*(curve2.x()-temp2.x())=curve2.y()-temp2.y();
                QMatrix M;
                M.setMatrix((curve3.x()*curve3.x())-(temp1.x()*temp1.x()),curve3.x()-temp1.x(),(curve3.x()*curve3.x())-(temp2.x()*temp2.x()),curve2.x()-temp2.x(),0,0);

                constA = (M.m22()/M.determinant())*(curve3.y()-temp1.y())-(M.m12()/M.determinant())*(curve3.y()-temp2.y());
                constB = -(M.m21()/M.determinant())*(curve3.y()-temp1.y())+(M.m11()/M.determinant())*(curve3.y()-temp2.y());

                constC = curve3.y()-(constA*curve3.x()*curve3.x())-(constB*curve3.x());

                //Equation of curve//

                double Y1,X1,Xdir,Ydir;
                qDebug()<<"circleIndices";

                Y1 = constA*(X1*X1)+constB*X1+constC;

                int k;
                double k1;
                if((curve3.x()-temp1.x())>=(curve3.y()-temp1.y()))
                {
                Xdir = (curve3.x()-temp1.x())/std::abs((curve3.x()-temp1.x()));
                Ydir = (curve3.y()-temp1.y())/std::abs((curve3.x()-temp1.x()));

                k1 = std::abs(curve3.x()-temp1.x());

              //  k1 = myDrawingA->start-5+std::abs((curve2.x()-temp1.x()));
                k=k1;
                }
                else
                {
                Xdir = (curve3.x()-temp1.x())/std::abs((curve3.y()-temp1.y()));
                Ydir = (curve3.y()-temp1.y())/std::abs((curve3.y()-temp1.y()));
                k1 = std::abs(curve3.y()-temp1.y());
                k=k1;
                }

                qDebug()<<"Temp4---";


                QPainterPath *painter1;
                double pointX1,pointY1;;

                qDebug()<<"constants "<<constA<<constB<<constC;

                painter1 = new QPainterPath;


                for (int j=1;j<k;j++)
                {
                    pointX1 = temp1.x()+j*Xdir;
                    pointY1= constA*(pointX1*pointX1)+constB*pointX1+constC;
                  //  qDebug()<<"Points Smoothen"<<pointX1<<pointY1;
                //   qDebug()<<"Points Smoothen"<<myDrawingA->pointsList.at(myDrawingA->start-5).y()+constA*(k*k*Xdir*Xdir)+constB*k*Xdir+constC;

                      if(j==1)
                       painter1->moveTo(pointX1,pointY1);
                  //
                      else
                          painter1->lineTo(pointX1,pointY1);

                   // myDrawingA->pointsList.insert(myDrawingA->start-5+j,QPointF(pointX1,pointY1));

                    //qDebug()<<"PointsX1Y1 "<<pointX1<<pointY1;
                }
            }

        }

        else if(circleStartIndex>circleStopIndex)
        {
            if(myDrawingA->start>=5)
            {
                Slope1 = ((curve3.y()-myDrawingA->pointsList.at(myDrawingA->start-5).y())/(curve3.x()-myDrawingA->pointsList.at(myDrawingA->start-5).y()));
                intercept1 = curve3.y()-Slope1*curve3.x();
            }
            if(myDrawingA->stop<=(myDrawingA->pointsList.length()-1-5))
            {
                Slope2 = ((curve2.y()-myDrawingA->pointsList.at(myDrawingA->stop+5).y())/(curve2.x()-myDrawingA->pointsList.at(myDrawingA->stop+5).y()));
                intercept2 = curve2.y()-Slope2*curve2.x();
            }

        }

      //  qDebug()<<"Slopes "<<Slope1<<Slope2<<intercept1<<intercept2;


         //Finding the Slope of curve
        QPainterPath nPath;
        for(int i=1;i<myDrawingA->pointsList.length();i++){

//                qDebug()<<"Temp3---";

            paintPath->lineTo(myDrawingA->pointsList.at(i).x(),myDrawingA->pointsList.at(i).y());
//            paintPath->arcTo(myDrawingA->pointsList.at(i).x(),myDrawingA->pointsList.at(i).y());

//                QGraphicsPathItem *path11;
//                path11=new QGraphicsPathItem;
//                path11->setPath(*paintPath);

//                path11->setPen(QPen(Qt::red,5));
//                addItem(path11);
        }
        QPainterPathStroker stroker;
        stroker.setJoinStyle(Qt::MiterJoin);
        nPath= (stroker.createStroke(*paintPath) + *paintPath).simplified();

        path->setPath(nPath);
        //        qDebug()<<"PointListSize1"<<myDrawingA->pointsList.length();
        //        path->setPath(*paintPath);

        //      //  qDebug()<<"circl"<<myDrawingA->pointsList<<myDrawingA->pointsList.at(myDrawingA->start);

        path->setPen(QPen(Qt::green,5));
        addItem(path);

        break;
    }
    default:
        break;
    }

    QGraphicsScene::mouseReleaseEvent(event);

    pressed = false;
    //this->setMode(NoMode);

}


void CustomScene::setMode(CustomScene::Mode mode){

    sceneMode=mode;

    //circle direction in this case if from +x,+y,-x,-y in image coordinate

    switch (sceneMode) {
    case Brush:
    {
        circleBrush= new QGraphicsEllipseItem;
        circleBrush->setPen(QPen(Qt::black));
        circleBrush->setBrush(QBrush(Qt::yellow));
        circleBrush->setRect(71,100,427,466);
        circleBrush->setFlag(QGraphicsItem::ItemIsMovable);
        addItem(circleBrush);


        double brushRadius=circleBrush->boundingRect().width()/2;

        double bushaAngleStep=1*PI/180;

        QPointF brushCentre=circleBrush->boundingRect().center();

        for(int i=0;i<brushPointCount;i++){
            pointListBrush.append(QPointF(brushRadius*cos(bushaAngleStep*i)+brushCentre.x(),brushRadius*sin(bushaAngleStep*i)+brushCentre.y()));
        }


        break;
    }
    default:
        break;
    }
}

