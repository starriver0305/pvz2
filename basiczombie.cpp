#include "basiczombie.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern int row[5],col[9];
extern Bare* bare[5][9];
extern int End;
void up(BasicZombie*);
class PoleVaultingZombie;
BasicZombie::BasicZombie(int _x, int _y)
{
    affix=new QMovie(":/new/prefix1/pictures/PointerUP.gif");
    affix->start();
    r=_x,c=_y;
    time1=time2=time5=time6=0;
    attack=1;
    speed=0.4;
    eaten=0;
    tag1=tag2=0;
    fire=0;
    faster=0;
    movie=NULL;
    die=NULL;
    change=0;
    freeze=0;
    fronzen=0;
    fast=0;
    flash=0;
    sputter=0;
    stronger=0;
    up1=up2=up3=0;
    attack=1;
    transparent=0;
    burn=0;
}

BasicZombie::~BasicZombie()
{
    if(movie){
        delete movie;
        movie=NULL;
    }
    if(die){
        delete die;
        die=NULL;
    }
    int val=rand()%250;
    Affix *affix=NULL;
    if(val>=0 && val<10){
        affix=new ZombieEndure();
    }
    if(val>=10 && val<20){
        affix=new ZombieFaster();
    }
    if(val>=20 && val<30){
        affix=new ZombieSputter();
    }
    if(val>=30 && val<60){
        int s=(val-30)/10;
        affix=new ZombieUp(s+1);
    }
    if(val>=60 && val<70){
        affix=new PlantFaster();
    }
    if(val>=70 && val<80){
        affix=new PlantFreeze();
    }
    if(val>=80 && val<90){
        affix=new PlantStronger();
    }
    if(val>=90 && val<100){
        affix=new PlantUp();
    }
    if(val>=110 && val<140){
        affix=new PlantRecovery();
    }
    if(val>=140 && val<150){
        affix=new PlantBurn();
    }
    if(val>=150 && val<160){
        affix=new UptoGatlingPea();
    }
    if(val>=160 && val<170){
        affix=new UptoSnowPea();
    }
    if(affix!=NULL){
        affix->setPos(this->scenePos());
        se->addItem(affix);
    }
}

QRectF BasicZombie::boundingRect() const
{
    return QRectF(-45,-85,120,145);
}

void BasicZombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(freeze){
        freeze++;
    }
    if(freeze==420){
        freeze=0;
    }
    if(freeze && movie){
        movie->setSpeed(60);
    }
    QImage image;
    if(movie){
        image=movie->currentImage();
        int color=0;
        if(!color && transparent && hp>0){
                for(int i=0;i<image.height();i++){
                    QRgb* line=(QRgb*)image.scanLine(i);
                    for(int j=0;j<image.width();j++){
                        if(line[j]==0){
                            continue;
                        }
                        image.setPixel(j,i,qRgba(qRed(line[j])/4,qGreen(line[j])/4,qBlue(line[j])/4,80));
                    }
                }
                color=1;
        }
        if(!color && freeze && !fire){
            for(int i=0;i<image.height();i++){
                QRgb* line=(QRgb*)image.scanLine(i);
                for(int j=0;j<image.width();j++){
                    if(line[j]==0){
                        continue;
                    }
                    image.setPixel(j,i,qRgb(qRed(line[j]),qGreen(line[j]),200));
                }
            }
            color=1;
        }
        else if(!color && fast && hp>0){
            for(int i=0;i<image.height();i++){
                QRgb* line=(QRgb*)image.scanLine(i);
                for(int j=0;j<image.width();j++){
                    if(line[j]==0){
                        continue;
                    }
                    image.setPixel(j,i,qRgb(200,qGreen(line[j]),qBlue(line[j])));
                }
            }
            color=1;
        }
        else if(!color && stronger && hp>0){
            for(int i=0;i<image.height();i++){
                QRgb* line=(QRgb*)image.scanLine(i);
                for(int j=0;j<image.width();j++){
                    if(line[j]==0){
                        continue;
                    }
                    image.setPixel(j,i,qRgb(200,qGreen(line[j]),200));
                }
            }
            color=1;
        }
        else if(!color && sputter && hp>0){
            for(int i=0;i<image.height();i++){
                QRgb* line=(QRgb*)image.scanLine(i);
                for(int j=0;j<image.width();j++){
                    if(line[j]==0){
                        continue;
                    }
                    image.setPixel(j,i,qRgb(qRed(line[j]),150,qBlue(line[j])));
                }
            }
            color=1;
        }
        QRectF rect=boundingRect();
        painter->drawImage(QRectF(rect.x(),rect.y(),rect.width(),rect.height()-10),image);
    }
    if(fronzen && hp>0){
        painter->drawImage(QRectF(10,25,40,30),QImage(":/new/prefix1/pictures/icsTrap.png"));
    }
    if(die){
        image=die->currentImage();
        if(freeze && !fire){
            for(int i=0;i<image.height();i++){
                QRgb* line=(QRgb*)image.scanLine(i);
                for(int j=0;j<image.width();j++){
                    if(line[j]==0){
                        continue;
                    }
                    image.setPixel(j,i,qRgb(qRed(line[j]),qGreen(line[j]),200));
                }
            }
        }
        painter->drawImage(boundingRect(),image);
    }
    if(hp>0){
        QBrush brush(Qt::red);
        painter->setBrush(brush);
        double rate = (double)hp/thp;
        painter->drawRect(-10,-60,60*rate,7);
        QPen pen(Qt::yellow);
        painter->setPen(pen);
        int cnt=0;
        if((up1 || up2 || up3) && cnt<2){
            painter->drawText(QPoint(10,48+cnt*10),"Revive");
            image=affix->currentImage();
            painter->drawImage(QRectF(48,40+cnt*10,10,10),image);
            cnt++;
        }
        if(stronger && cnt<2){
            painter->drawText(QPoint(30,48+cnt*10),"Hp");
            image=affix->currentImage();
            painter->drawImage(QRectF(48,40+cnt*10,10,10),image);
            cnt++;
        }
        if(fast && cnt<2){
            painter->drawText(QPoint(10,48+cnt*10),"Faster");
            image=affix->currentImage();
            painter->drawImage(QRectF(48,40+cnt*10,10,10),image);
            cnt++;
        }
        if(flash && cnt<2){
            painter->drawText(QPoint(10,48+cnt*10),"Flash");
            image=affix->currentImage();
            painter->drawImage(QRectF(48,40+cnt*10,10,10),image);
            cnt++;
        }
        if(attack>1 && cnt<2){
            painter->drawText(QPoint(10,48+cnt*10),"Stronger");
            image=affix->currentImage();
            painter->drawImage(QRectF(48,40+cnt*10,10,10),image);
            cnt++;
        }
        if(sputter && cnt<2){
            painter->drawText(QPoint(10,48+cnt*10),"Sputter");
            image=affix->currentImage();
            painter->drawImage(QRectF(48,40+cnt*10,10,10),image);
            cnt++;
        }
    }
}

void BasicZombie::advance(int phase)
{
    Q_UNUSED(phase)
    if(End){
        return;
    }
    if(x<0 || y<0){
        End=1;
        GameOver *gameover=new GameOver();
        gameover->setPos(600,350);
        se->addItem(gameover);
        return;
    }
    if(eaten && (!up1 && !up2 && !up3)){
        if(!transparent){
            row[r]--;
            col[c]--;
        }
        se->removeItem(this);
        delete this;
        return;
    }
    if(hp<=0){
        bool tag=up1 || up2 || up3;
        if(tag){
            if(!transparent){
                row[r]--;
                col[c]--;
            }
            up(this);
            delete this;
            return;
        }
        if(movie && freeze && !fire){
            movie->setSpeed(40);
        }
        if(die && freeze && !fire){
            die->setSpeed(60);
        }
        if(time2==0){
            if(!transparent){
                row[r]--;
                col[c]--;
            }
            if(!fire){
                setMovie(die1);
                setDie(die2);
            }
            else{
                movie=new QMovie(":/new/prefix1/pictures/Zombie/BoomDie.gif");
                movie->start();
            }
        }
        time2+=2;
        if(time2==500 && !fire){
            se->removeItem(this);
            delete this;
            return;
        }
        if(time2==850 && fire){
            se->removeItem(this);
            delete this;
            return;
        }
        if(!tag){
            update();
        }
        return;
    }
    if(fronzen){
        if(!movie){
            fronzen=0;
        }
        else{
            fronzen++;
            if(fronzen==2){
                movie->stop();
                speed1=speed;
                speed=0;
            }
            if(fronzen==350){
                movie->start();
                speed=speed1;
                fronzen=0;
            }
        }
    }
    if(sputter){
        int _x=this->scenePos().x();
        int _y=this->scenePos().y();
        QList<QGraphicsItem*>items=se->items(QRectF(_x-60,_y-75,120,150));
        foreach(QGraphicsItem* item,items){
            BasicPlant *plant=dynamic_cast<BasicPlant*>(item);
            if(plant && plant->hp>0){
                plant->hp-=2;
            }
        }
    }
    if(burn){
        time6++;
        if(time6%80==0){
            hp-=60;
        }
        if(time6==480){
            time6=0;
            burn=0;
        }
    }
}

void BasicZombie::setMovie(QString str)
{
    if(movie){
        delete movie;
    }
    movie=new QMovie(str);
    if(fast){
        setSpeed();
    }
    movie->start();
}

void BasicZombie::setDie(QString str)
{
    if(die){
        delete die;
    }
    die=new QMovie(str);
    die->start();
}

void BasicZombie::setSpeed()
{
    if(movie && hp>0){
        movie->setSpeed(300);
    }
}

void BasicZombie::setFaster(int val)
{
    speed*=val;
}

void BasicZombie::move()
{
    if(End){
        return;
    }
    if(!transparent){
        row[r]--;
        col[c]--;
    }
    Bare *b=bare[x][y];
    QPoint pointer=this->pos().toPoint();
    QPoint p=b->pos().toPoint();
    if(fabs(p.x()-pointer.x())<=6 && fabs(p.y()-pointer.y())<=10){
        if(change==0){
            change=1;
            direction=b->ne;
        }
        r=x,c=y;
        switch(b->ne){
        case 0:y--;break;
        case 1:x--;break;
        case 2:x++;break;
        }
    }
    else{
        change=0;
    }
    if(freeze){
        speed/=2;
    }
    switch(direction){
    case 0:tag1+=speed;break;
    case 1:tag2-=speed;break;
    case 2:tag2+=speed;break;
    }
    if(freeze){
        speed*=2;
    }
    if(!transparent){
        row[r]++;
        col[c]++;
    }
    this->setPos(src1-tag1,src2+tag2);
}
