#include "tallnut.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
TallNut::TallNut()
{
    hp=thp=5000;
    movie=new QMovie(":/new/prefix1/pictures/TallNut/TallNut.gif");
    movie->start();
}

QRectF TallNut::boundingRect() const
{
    return QRectF(-35,-45,70,110);
}

void TallNut::advance(int phase)
{
    Q_UNUSED(phase)
    if(!isset){
        return;
    }
    if(2998<=hp && hp<=3002){
        delete movie;
        movie=new QMovie(":/new/prefix1/pictures/TallNut/TallnutCracked1.gif");
        movie->start();
    }
    if(998<=hp && hp<=1002){
        delete movie;
        movie=new QMovie(":/new/prefix1/pictures/TallNut/TallnutCracked2.gif");
        movie->start();
    }
    QPoint point=this->scenePos().toPoint();
    QRectF rec(point.x()-10,point.y()-10,20,20);
    QList<QGraphicsItem*>items=se->items(rec);
    foreach (QGraphicsItem* item, items) {
        QPoint p=item->scenePos().toPoint();
        if(fabs(point.x()-p.x())<=10 && fabs(point.y()-p.y())<=10){
            BasicZombie *zombie=dynamic_cast<BasicZombie*>(item);
            if(zombie){
                if(zombie->hp>0){
                    if(!zombie->fronzen){
                        hp-=zombie->attack;
                    }
                    if(zombie->flash && !zombie->time5){
                        zombie->time5=1;
                    }
                    else if(zombie->time5==0){
                        zombie->state=1;
                        if(freeze){
                            zombie->freeze=1;
                        }
                        if(burn){
                            zombie->burn=1;
                            zombie->time6=0;
                        }
                    }
                }
            }
        }
    }
    update();
    if(hp<=0){
        foreach (QGraphicsItem* item, items) {
            QPoint p=item->scenePos().toPoint();
            if(fabs(point.x()-p.x())<=10 && fabs(point.y()-p.y())<=10){
                BasicZombie *zombie=dynamic_cast<BasicZombie*>(item);
                if(zombie){
                    zombie->state=0;
                }
            }
        }
        delete this;
    }
}

