//
// Created by emin on 15.07.2019.
//

#include "Projectile.h"
#include "SimpleAudioEngine.h"

Projectile::Projectile(void) {
    log("I am bullet:constructor");
}

Projectile::~Projectile(void) {
}

bool Projectile::init() {
    winSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    this->initWithFile("projectile.png");

    this->setPosition(winSize.width, winSize.height);
    this->scheduleUpdate();
    return true;
}

void Projectile::update(float dT) {
    if (isOnAir) {
        this->runAction(MoveBy::create(dT, Vec2(0, 2)));
    }

    if(this->getPosition().y>winSize.height){
        hideAndStop();
    }
}

void Projectile::hideAndStop() {
    isOnAir = false;
    this->setPosition(winSize.width - 100, winSize.height + 100);
    this->setVisible(false);
}

void Projectile::shoot(Vec2 spawnPoint)
{
    this->setPosition(spawnPoint);
    this->setVisible(true);
    isOnAir = true;
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/laser2.wav");
}