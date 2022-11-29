#ifndef UPTOGATLINGPEA_H
#define UPTOGATLINGPEA_H
#include"repeater.h"
#include"peashooter.h"
#include"snowpea.h"
#include"affix.h"
#include"bare.h"
#include"grass.h"
class UptoGatlingPea:public Affix
{
public:
    UptoGatlingPea();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // UPTOGATLINGPEA_H
