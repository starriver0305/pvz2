#include "snowpea.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern int row[5],col[9];
extern Grass* grass[5][9];
SnowPea::SnowPea(int _x, int _y):BasicPlant(_x,_y)
{
    movie=new QMovie(":/new/prefix1/pictures/SnowPea/SnowPea.gif");
    movie->start();
    hp=thp=10000;
    speed=140;
}

QRectF SnowPea::boundingRect() const
{
    return QRectF(-35,-35,70,80);
}

void SnowPea::advance(int phase)
{
    Q_UNUSED(phase)
    if(!isset){
        return;
    }
    hp--;
    if(row[x]){
        time1+=1;
        if(time1==10){
            if(freeze){
                Pea* pea=new Pea(2,this->scenePos().x()+20,this->scenePos().y()-10,2,injury,freeze,stronger,burn);
                se->addItem(pea);
            }
            else{
                Pea* pea=new Pea(1,this->scenePos().x()+20,this->scenePos().y()-10,2,injury,freeze,stronger,burn);
                se->addItem(pea);
            }
        }
        if(time1>=speed){
            time1=0;
        }
    }
    else{
        time1=0;
    }
    update();
    if(hp<=0){
        if(tag==0){
            Peashooter *shooter=new Peashooter(x,y);
            Grass* g=grass[x][y];
            shooter->setParentItem(g);
            shooter->hp=php;
            shooter->freeze=freeze;
            shooter->stronger=stronger;
            shooter->burn=burn;
            shooter->speed=speed;
        }
        if(tag==1){
            Repeater *shooter=new Repeater(x,y);
            Grass* g=grass[x][y];
            shooter->setParentItem(g);
            shooter->hp=php;
            shooter->freeze=freeze;
            shooter->stronger=stronger;
            shooter->burn=burn;
            shooter->speed=speed;
        }
        delete this;
    }
}
