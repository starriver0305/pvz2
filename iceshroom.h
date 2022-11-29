#ifndef ICESHROOM_H
#define ICESHROOM_H

#include"basicplant.h"
#include<QSize>
#include"basiczombie.h"
class IceShroom:public BasicPlant
{
public:
    IceShroom();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
};
#endif // ICESHROOM_H
