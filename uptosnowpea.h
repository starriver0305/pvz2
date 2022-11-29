#ifndef UPTOSNOWPEA_H
#define UPTOSNOWPEA_H
#include"repeater.h"
#include"peashooter.h"
#include"snowpea.h"
#include"affix.h"
#include"bare.h"
#include"grass.h"
class UptoSnowPea:public Affix
{
public:
    UptoSnowPea();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // UPTOSNOWPEA_H
