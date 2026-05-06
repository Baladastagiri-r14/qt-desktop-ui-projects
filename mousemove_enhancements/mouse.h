#ifndef MOUSE_H
#define MOUSE_H
#include <QGraphicsScene>
#include <QPointer>
#include <QGraphicsSceneMouseEvent>

class mouse : public QGraphicsScene
{
    Q_OBJECT
public:
    mouse();
    int deltaY;
    float deltaX = NULL;
    float angleInDegrees=NULL;
    bool horizantal;
    bool vartical;
    float heigh =0;
    float widh = 0;




private:
    QPointF     startingpoint;



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:
    void buttonclick();
    void doubleclick();


};

#endif // MOUSE_H
