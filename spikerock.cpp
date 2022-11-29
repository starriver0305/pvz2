#include "spikerock.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
Spikerock::Spikerock():BasicPlant(0,0)
{
    movie=new QMovie(":/new/prefix1/pictures/Spikerock/Spikerock.gif");
    movie->start();
    hp=thp=10000;
    speed=100;
}

QRectF Spikerock::boundingRect() const
{
    return QRectF(-35,10,70,40);
}

void Spikerock::advance(int phase)
{
    Q_UNUSED(phase)
    if(!isset){
        return;
    }
    QPoint point=this->scenePos().toPoint();
    QRectF rec(point.x()-50,point.y()-50,100,100);
    QList<QGraphicsItem*>items=se->items(rec);
    int tag=0;
    foreach (QGraphicsItem* item, items) {
        QPoint p=item->scenePos().toPoint();
        int x=point.x()-p.x();
        int y=point.y()-p.y();
        if(((x>=0 && x<=100) || (x<=0 && x>=-20)) && (y>=-30 && y<=60)){
            BasicZombie *zombie=dynamic_cast<BasicZombie*>(item);
            if(zombie){
                if(zombie->flash && !zombie->time5){
                    zombie->time5=1;
                }
                else if((!tag ||injury) &&!zombie->time5 && !zombie->flash){
                    if(zombie->hp>0){
                        if(speed==100){
                            zombie->hp-=2*stronger;
                        }
                        else{
                            zombie->hp-=4*stronger;
                        }
                        hp-=1;
                        if(freeze){
                            zombie->freeze=1;
                        }
                        if(burn){
                            zombie->burn=1;
                            zombie->time6=0;
                        }
                    }
                    tag=1;
                }
            }
        }
    }
    if(hp==600){
        delete movie;
        movie=new QMovie(":/new/prefix1/pictures/Spikerock/SpikerockCracked1.gif");
        movie->start();
    }
    if(hp==300){
        delete movie;
        movie=new QMovie(":/new/prefix1/pictures/Spikerock/SpikerockCracked2.gif");
        movie->start();
    }
    update();
    if(hp<=0){
        delete this;
    }
}

void Spikerock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image=movie->currentImage();
    QRectF rect=boundingRect();
    painter->drawImage(QRectF(rect.x(),rect.y()+10,rect.width(),rect.height()-10),image);
    if(isset){
        QBrush brush(Qt::red);
        painter->setBrush(brush);
        double rate = (double)hp/thp;
        painter->drawRect(-30,10,60*rate,7);
    }
}

