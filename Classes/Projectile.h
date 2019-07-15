//
// Created by emin on 15.07.2019.
//

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "cocos2d.h"

using namespace cocos2d;

class Projectile : public Sprite {

public:
    CREATE_FUNC(Projectile);

    ~Projectile(void);

    bool init();

    void update(float dT);

    void hideAndStop();

    void shoot(Vec2 spawnPoint);

private:
    Projectile(void);
    bool isOnAir;
    Size winSize;
    Vec2 origin;
};


#endif //__PROJECTILE_H__
