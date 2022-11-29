#include "screendoorzombie.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern Bare* bare[5][9];
extern int row[5],col[9];
ScreenDoorZombie::ScreenDoorZombie(int _r, int _c):BasicZombie(_r,_c)
{
    state=2;
    flag1=flag2=flag3=0;
    setMovie(":/new/prefix1/pictures/ScreenDoorZombie/ScreenDoorZombie.gif");
    die1=":/new/prefix1/pictures/Zombie/ZombieDie.gif";
    die2=":/new/prefix1/pictures/Zombie/ZombieHead.gif";
    hp=thp=2200;
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
}

QRectF ScreenDoorZombie::boundingRect() const
{
    return QRectF(-45,-65,110,130);
}

void ScreenDoorZombie::advance(int phase)
{
    BasicZombie::advance(phase);
    if(hp<=0){
        return;
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
        if(hp<700){
            setMovie(":/new/prefix1/pictures/Zombie/Zombie.gif");
        }
        else{
            setMovie(":/new/prefix1/pictures/ScreenDoorZombie/ScreenDoorZombie.gif");
        }
        flash=0;
        speed=0.5;
        time5=0;
    }
    if(hp<=700 && hp>0){
        if(state==1){
            if(flag1 && flag3){
                update();
                return;
            }
            setMovie(":/new/prefix1/pictures/Zombie/ZombieAttack.gif");
            flag1=1;
            flag3=1;
            flag2=0;
            update();
            return;
        }
        else{
            if(!flag2 || !flag3){
                setMovie(":/new/prefix1/pictures/Zombie/Zombie.gif");
                flag2=1;
                flag3=1;
                flag1=0;
            }
        }
    }
    else if(hp>700){
        if(state==1){
            if(flag1){
                update();
                return;
            }
            setMovie(":/new/prefix1/pictures/ScreenDoorZombie/ScreenDoorZombieAttack.gif");
            flag1=1;
            flag2=0;
            update();
            return;
        }
        else{
            if(!flag2){
                setMovie(":/new/prefix1/pictures/ScreenDoorZombie/ScreenDoorZombie.gif");
                flag2=1;
                flag1=0;
            }
        }
    }
    if(hp>0){
        move();
    }
}
