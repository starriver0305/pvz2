#include "polevaultingzombie.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern Bare* bare[5][9];
extern int row[5],col[9];
void up(BasicZombie*);
PoleVaultingZombie::PoleVaultingZombie(int _r, int _c):BasicZombie(_r,_c)
{
    hp=thp=1500;
    state=2;
    flag1=flag2=0;
    setMovie(":/new/prefix1/pictures/PoleVaultingZombie/PoleVaultingZombie.gif");
    speed=0.65;
    jump=0;
    int val=rand()%120;
    if(val>=0 && val<20){
        fast=1;
        speed*=2;
        setSpeed();
    }
    if(val>=20 && val<40){
        sputter=1;
    }
    if(val>=40 && val<60){
        attack*=2;
        stronger=1;
    }
    if(val>=60 && val<70){
        transparent=1;
    }
    if(val>=70 && val<80){
        flash=1;
    }
    flash=1;
}
void PoleVaultingZombie::advance(int phase){
    Q_UNUSED(phase)
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
        if(time1==0){
            if(!transparent){
                row[r]--;
                col[c]--;
            }
            if(movie){
                delete movie;
            }
            if(die){
                delete die;
            }
            if(!fire){
                movie=new QMovie(":/new/prefix1/pictures/PoleVaultingZombie/PoleVaultingZombieDie.gif");
                die=new QMovie(":/new/prefix1/pictures/PoleVaultingZombie/PoleVaultingZombieHead.gif");
                movie->start();
                die->start();
            }
            else{
                this->setScale(this->scale()*0.65);
                movie=new QMovie(":/new/prefix1/pictures/Zombie/BoomDie.gif");
                movie->start();
            }
        }
        time1+=2;
        if(time1==500 && !fire){
            delete this;
            return;
        }
        if(time1==850 && fire){
            delete this;
            return;
        }
        update();
        return;
    }
    if(x<0 || y<0){
        GameOver *gameover=new GameOver();
        gameover->setPos(600,350);
        se->addItem(gameover);
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
    if(time5==1){
        delete movie;
        movie=NULL;
        speed=12;
        time5++;
     }
    if(time5>0 && time5<30){
        time5++;
    }
    if(time5==20){
        qDebug()<<jump;
        if(jump==0){
            setMovie(":/new/prefix1/pictures/PoleVaultingZombie/PoleVaultingZombie.gif");
        }
        else if(jump==2){
            setMovie(":/new/prefix1/pictures/PoleVaultingZombie/PoleVaultingZombieWalk.gif");
        }
        flash=0;
        speed=0.5;
        time5=0;
    }
    if(state==1 && jump!=1){
        if(flag1){
            update();
            return;
        }
        if(movie){
            delete movie;
        }
        movie=new QMovie(":/new/prefix1/pictures/PoleVaultingZombie/PoleVaultingZombieAttack.gif");
        if(fast){
            setSpeed();
        }
        movie->start();
        flag1=1;
        flag2=0;
        update();
        return;
    }
    else if(state==0){
        if(!flag2){
            if(movie){
                delete movie;
            }
            movie=new QMovie(":/new/prefix1/pictures/PoleVaultingZombie/PoleVaultingZombieWalk.gif");
            if(fast){
                setSpeed();
            }
            movie->start();
            flag2=1;
            flag1=0;
        }
    }
    if(jump==0){
        int _x=this->scenePos().x();
        int _y=this->scenePos().y();
        QList<QGraphicsItem*>items=se->items(QRectF(_x-5,_y-20,10,40));
        foreach(QGraphicsItem* item,items){
            BasicPlant* plant=dynamic_cast<BasicPlant*>(item);
            CobCannon* cob=dynamic_cast<CobCannon*>(item);
            if(!cob && plant && plant->hp>0 && plant->isset && !flash){
                jump=1;
            }
        }
    }
    if(hp>0){
        if(jump==1){
            if(time2>=0 && time2<50){
                speed=0;
            }
            if(time2>=48 && time2<=80){
                speed=4;
            }
            else{
                speed=0.5;
            }
            if(time2==0){
                delete movie;
                movie=new QMovie(":/new/prefix1/pictures/PoleVaultingZombie/PoleVaultingZombieJump.gif");
                movie->start();
            }
            if(time2==50){
                delete movie;
                movie=new QMovie(":/new/prefix1/pictures/PoleVaultingZombie/PoleVaultingZombieJump2.gif");
                movie->start();
            }
            if(time2==100){
                delete movie;
                movie=new QMovie(":/new/prefix1/pictures/PoleVaultingZombie/PoleVaultingZombieWalk.gif");
                if(fast){
                    setSpeed();
                }
                movie->start();
                jump=2;
                state=0;
            }
            time2++;
        }
        move();
    }
}
QRectF PoleVaultingZombie::boundingRect() const{
    return QRectF(-45,-75,140,150);
}
void PoleVaultingZombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(freeze){
        freeze++;
    }
    if(freeze==420){
        freeze=0;
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
        else if(!color && freeze && !fire){
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
        painter->drawImage(QRectF(-100,-115,180,180),image);
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
        painter->drawImage(QRectF(-100,-115,180,180),image);
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
