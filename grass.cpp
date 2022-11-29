#include "grass.h"
QRectF Grass::boundingRect() const
{
    return QRectF(-39,-52,78,104);
}

void Grass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPixmap pixmap(":/new/prefix1/pictures/grass.png");
    painter->drawPixmap(QRect(-39,-52,78,104),pixmap);
}
Grass::Grass(int _r,int _c)
{
    tag=1;
    r=_r;
    c=_c;
}
