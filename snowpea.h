#ifndef SNOWPEA_H
#define SNOWPEA_H

#include"basicplant.h"
#include"peashooter.h"
#include"repeater.h"
#include"pea.h"
#include"grass.h"
class SnowPea:public BasicPlant
{
public:
    SnowPea(int _x=0, int _y=0);
    QRectF boundingRect() const;
    void advance(int phase);
    int php;
    int tag;
};

#endif // SNOWPEA_H
