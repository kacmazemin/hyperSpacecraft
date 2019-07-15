//
// Created by emin on 14.07.2019.
//

#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "EnemyShip.h"
#include "Projectile.h"


using namespace cocos2d;

class GameLayer : public Scene {

public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref *pSender);


    void update(float dT);
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);

    EnemyShip *enemyShip;
    Projectile *projectile;

    Vector<EnemyShip *> enemyShipPool;
    Vector<Projectile *> projectilePool;
    Label *score;

    int enemyShipIndex = 0;
    float enemyShipTimer;

    int projectileIndex = 0;
    float projectileTimer;




private:
    Sprite *mySpaceCraft;
    Sprite *bgImage;
    Size winSize;
    Vec2 origin;
    Vec2 touchLocation;
    int iEnemyCount;
    int iProjectileCount;
    int scoreCount;


    void moveLeft(Sprite *sprite);

    void moveRight(Sprite *sprite);

    void spawmEnemies(int enemyNumber);

    void spawnProjectiles(int projectileNumber);

    bool TouchBegan(Touch *touch, Event *event);

    bool checkBoxCollision(Sprite *box1, Sprite *box2);
};

#endif // __GAMELAYER_H__
