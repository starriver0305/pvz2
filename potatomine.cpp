#include "potatomine.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
PotatoMine::PotatoMine()
{
    time1=0;
    state=0;
    growth=0;
    die=NULL;
    movie=new QMovie(":/new/prefix1/pictures/PotatoMine/PotatoMine.gif");
    movie->start();
    hp=thp=2000;
    speed=1500;
}

QRectF PotatoMine::boundingRect() const
{
    return QRectF(-35,-20,70,70);
}

void PotatoMine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image=movie->currentImage();
    painter->drawImage(QRectF(-35,-20,70,70),image);
    if(die){
        image=die->currentImage();
        painter->drawImage(QRectF(-35,-20,70,70),image);
    }
    if(isset){
        QBrush brush(Qt::red);
        painter->setBrush(brush);
        double rate = (double)hp/thp;
        painter->drawRect(-30,-20,60*rate,7);
    }
}

void PotatoMine::advance(int phase)
{
    Q_UNUSED(phase)
    if(!isset){
        return;
    }
    QPoint point=this->scenePos().toPoint();
    QRectF rec(point.x()-100,point.y()-50,200,100);
    QList<QGraphicsItem*>items=se->items(rec);
    if(state==1){
        if(time1==0){
            delete movie;
            movie=new QMovie(":/new/prefix1/pictures/PotatoMine/PotatoMine_mashed.gif");
            die=new QMovie(":/new/prefix1/pictures/PotatoMine/ExplosionSpudow.gif");
            movie->start();
            die->start();
            foreach (QGraphicsItem* item, items) {
                QPoint p=item->scenePos().toPoint();
                if(fabs(point.x()-p.x())<=60 && fabs(point.y()-p.y())<=30){
                    BasicZombie *zombie=dynamic_cast<BasicZombie*>(item);
                    if(zombie){
                        if(zombie->flash && !zombie->time5){
                            zombie->time5=1;
                        }
                        else if(zombie->hp>0 && (!time1 || injury) && !zombie->flash){
                            zombie->hp-=2000*stronger;
                            time1=2;
                            if(zombie->hp<=0){
                                zombie->eaten=1;
                            }
                        }
                    }
                }
            }
        }
        time1+=2;
        if(time1==300){
            delete movie;
            delete die;
            die=NULL;
            movie=new QMovie(":/new/prefix1/pictures/PotatoMine/PotatoMineNotReady.gif");
            movie->start();
            state=0;
            growth=1;
            time1=0;
        }
    }
    else if(!growth){
        foreach (QGraphicsItem* item, items) {
            QPoint p=item->scenePos().toPoint();
            if(fabs(point.x()-p.x())<=30 && fabs(point.y()-p.y())<=10){
                BasicZombie *zombie=dynamic_cast<BasicZombie*>(item);
                if(zombie && zombie->hp>0){
                    state=1;
                }
            }
        }
    }
    else if(growth){
        foreach (QGraphicsItem* item, items) {
            QPoint p=item->scenePos().toPoint();
            if(fabs(point.x()-p.x())<=30 && fabs(point.y()-p.y())<=10){
                BasicZombie *zombie=dynamic_cast<BasicZombie*>(item);
                if(zombie){
                    if(zombie->hp>0){
                        if(zombie->flash && !zombie->time5){
                            zombie->time5=1;
                        }
                        else if(!zombie->fronzen && !zombie->flash){
                            hp-=zombie->attack;
                            zombie->state=1;
                        }
                    }
                }
            }
        }
        if(hp<=0){
            foreach (QGraphicsItem* item, items) {
                QPoint p=item->scenePos().toPoint();
                if(fabs(point.x()-p.x())<=30 && fabs(point.y()-p.y())<=10){
                    BasicZombie *zombie=dynamic_cast<BasicZombie*>(item);
                    if(zombie){
                        if(zombie->hp>0){
                            zombie->state=0;
                        }
                    }
                }
            }
            delete this;
        }
        growth++;
        if(growth==speed){
            delete movie;
            movie=new QMovie(":/new/prefix1/pictures/PotatoMine/PotatoMine.gif");
            movie->start();
            growth=0;
            state=0;
            time1=0;
        }
    }
    update();
}
