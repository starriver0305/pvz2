#include "uptogatlingpea.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern Bare* bare[5][9];
extern Grass* grass[5][9];
UptoGatlingPea::UptoGatlingPea()
{
    movie=new QMovie(":/new/prefix1/pictures/card/gatlingpea.png");
    movie->start();
}

void UptoGatlingPea::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    Affix::mousePressEvent(event);
    point1=this->scenePos().toPoint();
    point2=QCursor::pos();
}

void UptoGatlingPea::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    point3=QCursor::pos();
    int x=point1.x()+point3.x()-point2.x();
    int y=point1.y()+point3.y()-point2.y();
    this->setPos(x,y);
}

void UptoGatlingPea::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    Affix::mouseReleaseEvent(event);
    QList<QGraphicsItem*>items=se->items(rect);
    foreach(QGraphicsItem* item,items){
        Peashooter *shooter=dynamic_cast<Peashooter*>(item);
        if(shooter){
            GatlingPea *pea=new GatlingPea(shooter->x,shooter->y);
            Grass* g=grass[shooter->x][shooter->y];
            pea->setParentItem(g);
            pea->tag=0;
            pea->php=shooter->hp;
            pea->stronger=shooter->stronger;
            pea->speed=shooter->speed;
            pea->freeze=shooter->freeze;
            pea->burn=shooter->burn;
            delete shooter;
            delete this;
            return;
        }
        Repeater *repeater=dynamic_cast<Repeater*>(item);
        if(repeater){
            GatlingPea *pea=new GatlingPea(repeater->x,repeater->y);
            Grass* g=grass[repeater->x][repeater->y];
            pea->setParentItem(g);
            pea->tag=1;
            pea->php=repeater->hp;
            pea->stronger=repeater->stronger;
            pea->speed=repeater->speed;
            pea->freeze=repeater->freeze;
            pea->burn=repeater->burn;
            delete repeater;
            delete this;
            return;
        }
    }
    this->setPos(point1);
}
