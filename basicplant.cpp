#include "basicplant.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern int row[5],col[9];
BasicPlant::BasicPlant(int _x, int _y)
{
    affix=new QMovie(":/new/prefix1/pictures/PointerUP.gif");
    affix->start();
    x=_x;
    y=_y;
    time1=time2=time3=0;
    injury=0;
    freeze=0;
    isset=1;
    stronger=1;
    burn=0;
    int val=rand()%100;
    if(val>=0 && val<10){
        injury=1;
    }
    if(val>=10 && val<20){
        freeze=1;
    }
    if(val>=20 && val<30){
        stronger*=2;
    }
    if(val>=30 && val<40){
        burn=1;
    }
    burn=1;
    stronger=2;
}

BasicPlant::~BasicPlant()
{
    if(movie){
        delete movie;
    }
}

QRectF BasicPlant::boundingRect() const
{
    return QRectF(-40,-40,80,80);
}

void BasicPlant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image=movie->currentImage();
    QRectF rect=boundingRect();
    painter->drawImage(QRectF(rect.x(),rect.y()+10,rect.width(),rect.height()-30),image);
    if(isset){
        QBrush brush(Qt::red);
        painter->setBrush(brush);
        double rate = (double)hp/thp;
        painter->drawRect(-30,-35,60*rate,7);
        QPen pen(Qt::yellow);
        painter->setPen(pen);
        int cnt=0;
        if(freeze && cnt<2){
            painter->drawText(QPoint(-18,38+cnt*10),"Freeze");
            image=affix->currentImage();
            painter->drawImage(QRectF(16,29+cnt*10,10,10),image);
            cnt++;
        }
        if(stronger>1 && cnt<2){
            painter->drawText(QPoint(-18,38+cnt*10),"Stronger");
            image=affix->currentImage();
            painter->drawImage(QRectF(16,29+cnt*10,10,10),image);
            cnt++;
        }
        if(burn && cnt<2){
            painter->drawText(QPoint(-18,38+cnt*10),"Burn");
            image=affix->currentImage();
            painter->drawImage(QRectF(16,29+cnt*10,10,10),image);
            cnt++;
        }
        if(injury && cnt<2){
            painter->drawText(QPoint(-18,38+cnt*10),"AOE");
            image=affix->currentImage();
            painter->drawImage(QRectF(16,29+cnt*10,10,10),image);
            cnt++;
        }
    }
}

void BasicPlant::advance(int phase)
{
    Q_UNUSED(phase);
    update();
}
