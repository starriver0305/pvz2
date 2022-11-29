#include "cobcannon.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern int row[5],col[9];
extern void bomb(int x, int y);
CobCannon::CobCannon()
{
    movie=new QMovie(":/new/prefix1/pictures/CobCannon/CobCannon.gif");
    movie->start();
    hp=thp=10000;
    used=0;
    this->setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF CobCannon::boundingRect() const
{
    if(used && (time1>0 && time1<=400)){
        return QRectF(-170,-450,330,900);
    }
    return QRectF(-170,-100,330,200);
}

void CobCannon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image=movie->currentImage();
    if(!isset){
        painter->drawImage(boundingRect(),image);
    }
    if(isset){
        if(!used || (used && time1==0)){
            painter->drawImage(boundingRect(),image);
        }
        else if(used && (time1>400 && time1<=1320)){
            painter->drawImage(boundingRect(),image);
        }
        else if(used && (time1>1320 && time1<=1400)){
            painter->drawImage(QRectF(-160,-100,330,200),image);
        }
        else{
            painter->drawImage(QRectF(-130,-400,220,450),image);
        }
        QBrush brush(Qt::red);
        painter->setBrush(brush);
        double rate = (double)hp/thp;
        painter->drawRect(-30,-35,60*rate,7);
    }
}

void CobCannon::advance(int phase)
{
    Q_UNUSED(phase)
    if(!isset){
        return;
    }
    if(used){
        if(time1==0){
            delete movie;
            movie=new QMovie(":/new/prefix1/pictures/CobCannon/CobCannonAttack.gif");
            movie->start();
        }
        else if(time1==400){
            delete movie;
            movie=new QMovie(":/new/prefix1/pictures/CobCannon/CobCannonPre.gif");
            movie->start();
        }
        else if(time1==370){
            int x=this->scenePos().x()+point.x()-pointer.x()+40;
            int y=this->scenePos().y()+point.y()-pointer.y();
            bomb(x,y);
        }
        else if(time1==1320){
            delete movie;
            movie=new QMovie(":/new/prefix1/pictures/CobCannon/CobCannonIsOK.gif");
            movie->start();
        }
        else if(time1==1400){
            delete movie;
            movie=new QMovie(":/new/prefix1/pictures/CobCannon/CobCannon.gif");
            movie->start();
            time1=-1;
            used=0;
        }
        time1++;
    }
    hp--;
    if(hp<=0){
        delete this;
        return;
    }
    update();
}

void CobCannon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    if(used){
        return;
    }
    pointer=QCursor::pos();
    target=new CobTarget();
    se->addItem(target);
}

void CobCannon::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    if(used){
        return;
    }
    point=QCursor::pos();
    int x=this->scenePos().x()+point.x()-pointer.x()+40;
    int y=this->scenePos().y()+point.y()-pointer.y();
    target->setPos(x,y);
}

void CobCannon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    if(used){
        return;
    }
    used=1;
    point=QCursor::pos();
    delete target;
}
