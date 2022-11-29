#include "zombieflash.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern Bare* bare[5][9];
extern Grass* grass[5][9];
ZombieFlash::ZombieFlash():Affix()
{
    movie=new QMovie(":/new/prefix1/pictures/flash.jpg");
    movie->start();
    this->setScale(this->scale()*0.8);
}

void ZombieFlash::advance(int phase)
{
    Q_UNUSED(phase);
    Affix::advance(phase);
    if(time1>=1000){
        return;
    }
    QPoint point=this->scenePos().toPoint();
    rect=QRectF(point.x()-10,point.y()-10,20,20);
    QList<QGraphicsItem*>items=se->items(rect);
    foreach(QGraphicsItem* item,items){
        BasicZombie *zombie=dynamic_cast<BasicZombie*>(item);
        if(zombie && !zombie->flash && zombie->hp>0){
            zombie->flash=1;
            delete this;
            return;
        }
    }
}
