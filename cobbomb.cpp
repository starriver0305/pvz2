#include "cobbomb.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
CobBomb::CobBomb()
{
    movie=new QMovie(":/new/prefix1/pictures/CobCannon/CobArrive.gif");
    movie->start();
    time1=0;
    setZValue(10000);
}

QRectF CobBomb::boundingRect() const
{
    return QRectF(-150,-350,300,480);
}

void CobBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QImage image=movie->currentImage();
    painter->drawImage(boundingRect(),image);
}

void CobBomb::advance(int phase)
{
    Q_UNUSED(phase);
    update();
    time1++;
    QPoint point=this->scenePos().toPoint();
    int x=point.x();
    int y=point.y();
    if(time1==48){
        QList<QGraphicsItem*>items=se->items(QRectF(x-70,y-70,140,140));
        foreach(QGraphicsItem* item,items){
            BasicZombie *zombie=dynamic_cast<BasicZombie*>(item);
            if(zombie && zombie->hp>0){
                zombie->hp-=3000;
                if(zombie->hp<=0){
                    zombie->fire=1;
                }
            }
        }
    }
    if(time1==90){
        delete movie;
        delete this;
    }
}

