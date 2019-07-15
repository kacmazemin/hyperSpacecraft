//
// Created by emin on 14.07.2019.
//

#ifndef __ENEMYSHIP_H__
#define __ENEMYSHIP_H__

#include "cocos2d.h"

using namespace cocos2d;

class EnemyShip : public Sprite {

public:

    ~EnemyShip();

    static EnemyShip *createEnemy();

    bool initEnemyShip();

    void update(float dT);

    void hideAndStop();

    void attack(Vec2 attackPosition);

    bool IsAttacking();


    CREATE_FUNC(EnemyShip);
    Size winSize;
    Vec2 origin;
private:
    bool isAttacking;

    EnemyShip();
};

#endif //__ENEMYSHIP_H__