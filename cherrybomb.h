#ifndef CHERRYBOMB_H
#define CHERRYBOMB_H
#include"basiczombie.h"
class CherryBomb:public BasicPlant
{
public:
    CherryBomb();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
};
#endif // CHERRYBOMB_H
