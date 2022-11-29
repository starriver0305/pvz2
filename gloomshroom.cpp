#include "gloomshroom.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern int row[5],col[9];
static int dx[8]={0,-1,-1,-1,0,1,1,1},dy[8]={-1,-1,0,1,1,1,0,-1};
GloomShroom::GloomShroom(int _r, int _c):BasicPlant(_r,_c)
{
    movie=new QMovie(":/new/prefix1/pictures/GloomShroom/GloomShroom.gif");
    movie->start();
    time1=-1;
    hp=thp=10000;
    speed=120;
}

QRectF GloomShroom::boundingRect() const
{
    return QRectF(-40,-40,80,90);
}

void GloomShroom::advance(int phase)
{
    Q_UNUSED(phase)
    if(!isset){
        return;
    }
    hp--;
    bool tag=0;
    for(int i=0;i<8;i++){
        int _x=x+dx[i];
        int _y=y+dy[i];
        if(_x<0 || _y<0 || _x>=5 || _y>=9){
            continue;
        }
        tag |=row[_x] && col[_y];
    }
    if(tag){
        if(time1<=0){
            delete movie;
            movie=new QMovie(":/new/prefix1/pictures/GloomShroom/GloomShroomAttack.gif");
            movie->start();
        }
        if(time1==10){
            for(int i=0;i<8;i++){
                Pea *bullet=new Pea(3,this->scenePos().x(),this->scenePos().y(),i,injury,freeze,stronger,burn);
                se->addItem(bullet);
            }
        }
        if(time1==20){
            for(int i=0;i<8;i++){
                Pea *bullet=new Pea(3,this->scenePos().x(),this->scenePos().y(),i,injury,freeze,stronger,burn);
                se->addItem(bullet);
            }
        }
        if(time1==30){
            for(int i=0;i<8;i++){
                Pea *bullet=new Pea(3,this->scenePos().x(),this->scenePos().y(),i,injury,freeze,stronger,burn);
                se->addItem(bullet);
            }
        }
        time1++;
        if(time1>=speed){
            time1=0;
        }
    }
    else{
        if(time1!=-1){
            time1=-1;
            delete movie;
            movie=new QMovie(":/new/prefix1/pictures/GloomShroom/GloomShroom.gif");
            movie->start();
        }
    }
    update();
    if(hp<=0){
        delete this;
    }
}

