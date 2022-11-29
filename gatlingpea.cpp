#include "gatlingpea.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern int row[5],col[9];
extern Grass *grass[5][9];
GatlingPea::GatlingPea(int _x, int _y):BasicPlant(_x,_y)
{
    movie=new QMovie(":/new/prefix1/pictures/GatlingPea/GatlingPea.gif");
    movie->start();
    hp=thp=10000;
    speed=140;
}

QRectF GatlingPea::boundingRect() const
{
    return QRectF(-35,-35,70,80);
}

void GatlingPea::advance(int phase)
{
    Q_UNUSED(phase)
    if(!isset){
        return;
    }
    hp--;
    if(row[x]){
        time1++;
        if(time1==10){
            if(freeze){
                Pea* pea=new Pea(2,this->scenePos().x()+20,this->scenePos().y(),2,injury,freeze,stronger,burn);
                se->addItem(pea);
            }
            else{
                Pea* pea=new Pea(0,this->scenePos().x()+20,this->scenePos().y(),2,injury,freeze,stronger,burn);
                se->addItem(pea);
            }
        }
        if(time1==20){
            if(freeze){
                Pea* pea=new Pea(2,this->scenePos().x()+20,this->scenePos().y(),2,injury,freeze,stronger,burn);
                se->addItem(pea);
            }
            else{
                Pea* pea=new Pea(0,this->scenePos().x()+20,this->scenePos().y(),2,injury,freeze,stronger,burn);
                se->addItem(pea);
            }
        }
        if(time1==30){
            if(freeze){
                Pea* pea=new Pea(2,this->scenePos().x()+20,this->scenePos().y(),2,injury,freeze,stronger,burn);
                se->addItem(pea);
            }
            else{
                Pea* pea=new Pea(0,this->scenePos().x()+20,this->scenePos().y(),2,injury,freeze,stronger,burn);
                se->addItem(pea);
            }
        }
        if(time1==40){
            if(freeze){
                Pea* pea=new Pea(2,this->scenePos().x()+20,this->scenePos().y(),2,injury,freeze,stronger,burn);
                se->addItem(pea);
            }
            else{
                Pea* pea=new Pea(0,this->scenePos().x()+20,this->scenePos().y(),2,injury,freeze,stronger,burn);
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

