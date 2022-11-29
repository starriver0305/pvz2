#ifndef GATLINGPEA_H
#define GATLINGPEA_H

#include"basicplant.h"
#include"peashooter.h"
#include"repeater.h"
#include"pea.h"
#include"grass.h"
class GatlingPea:public BasicPlant
{
public:
    GatlingPea(int _x=0, int _y=0);
    QRectF boundingRect() const;
    void advance(int phase);
    int php;
    int tag;
};

#endif // GATLINGPEA_H
