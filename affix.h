#ifndef AFFIX_H
#define AFFIX_H
#include<QMovie>
#include<QPainter>
#include<QGraphicsItem>
#include<QTimer>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsView>
#include<QDebug>
#include"cobcannon.h"
class Affix:public QGraphicsItem
{
protected:
    QMovie *movie;
    int time1;
    QPoint prev,cur,point1,point2,point3;
    QRectF rect;
public:
    Affix();
    ~Affix();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // AFFIX_H
