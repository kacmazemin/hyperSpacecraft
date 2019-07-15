//
// Created by emin on 14.07.2019.
//

#include "EnemyShip.h"

USING_NS_CC;

EnemyShip::EnemyShip() {

}

EnemyShip::~EnemyShip() {

}

EnemyShip *EnemyShip::createEnemy() {

    EnemyShip *myEnemy = new EnemyShip();


    if (myEnemy && myEnemy->initEnemyShip()) {
        myEnemy->autorelease();
        return myEnemy;
    }

    CC_SAFE_DELETE(myEnemy);
    return NULL;
}

bool EnemyShip::initEnemyShip() {
    //enemy init
    winSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    this->initWithFile("enemyShip2.png");
    this->hideAndStop();

    this->scheduleUpdate();
    return true;
}

void EnemyShip::update(float dT) {

    if (isAttacking) {

        this->runAction(MoveBy::create(dT, Vec2(0, -1)));//def y value -0.25

        if (this->getPosition().y < this->getContentSize().height - 20) {

            hideAndStop();
        }
    }


}

void EnemyShip::hideAndStop() {
    isAttacking=false;
    this->setPosition(this->getPosition().x+50, winSize.height-50);
    this->setVisible(false);

}
void EnemyShip::attack(Vec2 attackPosition){
    isAttacking=true;
    this->setPosition(attackPosition);
    this->setVisible(true);
}

bool EnemyShip::IsAttacking(){
    return isAttacking;

}