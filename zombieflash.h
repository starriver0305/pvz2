#ifndef ZOMBIEFLASH_H
#define ZOMBIEFLASH_H

#include"basiczombie.h"
#include"affix.h"
#include"bare.h"
#include"grass.h"
class ZombieFlash:public Affix
{
public:
    ZombieFlash();
    QRectF boundingRect();
    void advance(int phase);
};

#endif // ZOMBIEFLASH_H
