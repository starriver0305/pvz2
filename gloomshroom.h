#ifndef GLOOMSHROOM_H
#define GLOOMSHROOM_H
#include"basiczombie.h"
#include"basicplant.h"
#include"pea.h"
class GloomShroom:public BasicPlant
{
public:
    GloomShroom(int _r=0, int _c=0);
    QRectF boundingRect() const;
    void advance(int phase);
};

#endif // GLOOMSHROOM_H
