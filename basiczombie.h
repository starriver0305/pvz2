#ifndef BASICZOMBIE_H
#define BASICZOMBIE_H

#include<QMovie>
#include<QPainter>
#include<QGraphicsItem>
#include<QTimer>
#include<QMouseEvent>
#include<QDebug>
#include<QGraphicsView>
#include<cstdlib>
#include"bare.h"
#include"gameover.h"
#include"zombieendure.h"
#include"zombiefaster.h"
#include"zombiesputter.h"
#include"zombieup.h"
#include"plantfaster.h"
#include"plantfreeze.h"
#include"planthurt.h"
#include"plantstronger.h"
#include"plantup.h"
#include"plantupdate.h"
#include"plantrecovery.h"
#include"plantburn.h"
#include"uptogatlingpea.h"
#include"uptosnowpea.h"
#include"affix.h"
class BasicZombie:public QGraphicsItem
{
protected:
    QMovie *movie;
    QMovie *die;
    QMovie *affix;
    int change;
public:
    BasicZombie(int x, int y);
    ~BasicZombie();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    void setMovie(QString str);
    void setDie(QString str);
    void setSpeed();
    void setFaster(int val);
    void move();
    int state;
    int hp;
    int thp;
    int x,y;
    double tag1,tag2;
    int r,c;
    int time1,time2,time5,time6;
    int eaten;
    int fire;
    int direction;
    double attack;
    double speed,speed1;
    int fast;
    int faster;
    int freeze;
    int fronzen;
    int flash;
    int sputter;
    int burn;
    int up1,up2,up3;
    int stronger;
    int transparent;
    double src1,src2;
    QString die1,die2;
};

#endif // BASICZOMBIE_H
