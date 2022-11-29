#include "newspaperzombie.h"
extern QGraphicsScene *se;
extern QGraphicsView *vw;
extern Bare* bare[5][9];
extern int row[5],col[9];
NewspaperZombie::NewspaperZombie(int _r, int _c):BasicZombie(_r, _c){
    state=2;
    flag1=flag2=0;
    setMovie(":/new/prefix1/pictures/NewspaperZombie/HeadWalk1.gif");
    die1=":/new/prefix1/pictures/NewspaperZombie/Die.gif";
    die2=":/new/prefix1/pictures/NewspaperZombie/Head.gif";
    hp=thp=1500;
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

QRectF NewspaperZombie::boundingRect() const{
    return QRectF(-35,-85,120,145);
}

void NewspaperZombie::advance(int phase){
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
        if(hp<500){
            setMovie(":/new/prefix1/pictures/NewspaperZombie/HeadWalk0.gif");
        }
        else{
            setMovie(":/new/prefix1/pictures/NewspaperZombie/HeadWalk1.gif");
        }
        flash=0;
        speed=0.5;
        time5=0;
    }
    if(hp<=500 && hp>0){
        faster=1;
        if(time1==0){
            setFaster(6);
            setMovie(":/new/prefix1/pictures/NewspaperZombie/LostNewspaper.gif");
        }
        if(time1==250){
            setMovie(":/new/prefix1/pictures/NewspaperZombie/HeadWalk0.gif");
            flag1=flag2=0;
        }
        time1+=2;
        if(time1<200){
            update();
            return;
        }
        if(state==1){
            if(flag1){
                update();
                return;
            }
            setMovie(":/new/prefix1/pictures/NewspaperZombie/HeadAttack0.gif");
            setSpeed();
            flag1=1;
            flag2=0;
            update();
            return;
        }
        else if(state==0){
            if(!flag2){
                setMovie(":/new/prefix1/pictures/NewspaperZombie/HeadWalk0.gif");
                flag2=1;
                flag1=0;
            }
        }
    }
    else if(hp>500){
        if(state==1){
            if(flag1){
                update();
                return;
            }
            setMovie(":/new/prefix1/pictures/NewspaperZombie/HeadAttack1.gif");
            flag1=1;
            flag2=0;
            update();
            return;
        }
        else{
            if(!flag2){
                setMovie(":/new/prefix1/pictures/NewspaperZombie/HeadWalk1.gif");
                flag2=1;
                flag1=0;
            }
        }
    }
    if(hp>0){
        move();
    }
}
