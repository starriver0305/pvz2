#ifndef COBCANNON_H
#define COBCANNON_H
#include"cobtarget.h"
#include<QGraphicsSceneMouseEvent>
#include"basicplant.h"
class CobCannon:public BasicPlant
{
private:
    QPoint pointer;
    CobTarget* target;
    int used;
    QPoint point;
public:
    CobCannon();
    QRectF boundingRect() const;
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};


#endif // COBCANNON_H
