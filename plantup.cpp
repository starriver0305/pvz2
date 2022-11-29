#include "plantup.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern Bare* bare[5][9];
extern Grass* grass[5][9];
PlantUp::PlantUp()
{
    movie=new QMovie(":/new/prefix1/pictures/PlantUp.png");
    movie->start();
}

void PlantUp::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    Affix::mousePressEvent(event);
    point1=this->scenePos().toPoint();
    point2=QCursor::pos();
}

void PlantUp::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    point3=QCursor::pos();
    int x=point1.x()+point3.x()-point2.x();
    int y=point1.y()+point3.y()-point2.y();
    this->setPos(x,y);
}

void PlantUp::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    Affix::mouseReleaseEvent(event);
    QList<QGraphicsItem*>items=se->items(rect);
    foreach(QGraphicsItem* item,items){
        BasicPlant *plant=dynamic_cast<BasicPlant*>(item);
        CobCannon* cob=dynamic_cast<CobCannon*>(item);
        if(plant && !cob){
            plant->thp*=2;
            plant->hp=plant->thp;
            plant->freeze=1;
            plant->injury=1;
            plant->speed*=0.7;
            delete this;
            return;
        }
    }
    this->setPos(point1);
}
