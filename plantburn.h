#ifndef PLANTBURN_H
#define PLANTBURN_H

#include"basicplant.h"
#include"affix.h"
#include"bare.h"
#include"grass.h"
class PlantBurn:public Affix
{
public:
    PlantBurn();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
#endif // PLANTBURN_H
