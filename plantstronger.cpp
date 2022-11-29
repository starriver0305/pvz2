#include "plantstronger.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern Bare* bare[5][9];
extern Grass* grass[5][9];
PlantStronger::PlantStronger()
{
    movie=new QMovie(":/new/prefix1/pictures/PlantRecovery.png");
    movie->start();
}

void PlantStronger::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    Affix::mousePressEvent(event);
    point1=this->scenePos().toPoint();
    point2=QCursor::pos();
}

void PlantStronger::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    point3=QCursor::pos();
    int x=point1.x()+point3.x()-point2.x();
    int y=point1.y()+point3.y()-point2.y();
    this->setPos(x,y);
}

void PlantStronger::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    Affix::mouseReleaseEvent(event);
    QList<QGraphicsItem*>items=se->items(rect);
    foreach(QGraphicsItem* item,items){
        BasicPlant *plant=dynamic_cast<BasicPlant*>(item);
        CobCannon* cob=dynamic_cast<CobCannon*>(item);
        if(plant && !cob){
            plant->hp*=1.5;
            plant->thp*=1.5;
            plant->stronger=1.5;
            delete this;
            return;
        }
    }
    this->setPos(point1);
}
