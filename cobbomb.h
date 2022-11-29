#ifndef COBBOMB_H
#define COBBOMB_H

#include"basiczombie.h"
#include"cobtarget.h"
class CobBomb:public QGraphicsItem
{
private:
    QMovie *movie;
    int time1;
public:
    CobBomb();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
};

#endif // COBBOMB_H
