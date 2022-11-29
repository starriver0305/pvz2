#include "cobtarget.h"

CobTarget::CobTarget()
{
    this->setZValue(10000);
}

QRectF CobTarget::boundingRect() const
{
    return QRectF(-30,-30,60,60);
}

void CobTarget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option)
    painter->drawImage(boundingRect(),QImage(":/new/prefix1/pictures/CobCannon/CobCannonTarget.png"));
}
