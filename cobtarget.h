#ifndef COBTARGET_H
#define COBTARGET_H

#include<QGraphicsItem>
#include<QPainter>
class CobTarget:public QGraphicsItem
{
public:
    CobTarget();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // COBTARGET_H
