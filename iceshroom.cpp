#include "iceshroom.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
IceShroom::IceShroom()
{
    movie=new QMovie(":/new/prefix1/pictures/IceShroom/IceShroom.gif");
    movie->start();
}

QRectF IceShroom::boundingRect() const
{
    return QRectF(-70,-70,140,140);
}

void IceShroom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image=movie->currentImage();
    painter->drawImage(QRectF(-35,-35,70,70),image);
}

void IceShroom::advance(int phase)
{
    Q_UNUSED(phase)
    if(!isset){
        return;
    }
    time1++;
    if(time1==100){
        QList<QGraphicsItem*>items=se->items();
        foreach(QGraphicsItem* item,items){
            BasicZombie *zombie=dynamic_cast<BasicZombie*>(item);
            if(zombie){
                zombie->fronzen=1;
                zombie->freeze=1;
            }
        }
        delete this;
        return;
    }
    update();
}

