//
// Created by emin on 14.07.2019.
//

#include <unistd.h>
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"

USING_NS_CC;

Scene *GameLayer::createScene() {

    return GameLayer::create();
}

// on "init" you need to initialize your instance
bool GameLayer::init() {

    if (!Scene::init()) {
        return false;
    }

    iEnemyCount = 0;

    winSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    bgImage = Sprite::create("bg.png");
    bgImage->setScale(5);
    this->addChild(bgImage);


    scoreLabel = Label::createWithTTF("Score", "fonts/arial.ttf", 10);
    scoreLabel->setPosition(Vec2(winSize.width - scoreLabel->getContentSize().width,
                                 winSize.height - scoreLabel->getContentSize().height));
    this->addChild(scoreLabel);


    //player init start
    mySpaceCraft = Sprite::create("Spacecraft.png");
    auto SpaceCraftContentSize = mySpaceCraft->getContentSize();
    mySpaceCraft->setPosition(
            Vec2(origin.x + winSize.width / 2, origin.y + SpaceCraftContentSize.height / 2));
    this->addChild(mySpaceCraft);
    //player init end

    //spawnObjects when game start
    this->spawmEnemies(50);
    this->spawnProjectiles(50);

    scheduleUpdate();

//touch listener
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::TouchBegan, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool GameLayer::TouchBegan(Touch *touch, Event *event) {
    touchLocation = touch->getLocation();
    if (touchLocation.x >
        winSize.width / 2)//if touch left of viewport move left, if right move right
    {
        moveRight(mySpaceCraft);
    } else {
        moveLeft(mySpaceCraft);
    }
    return true;
}

void GameLayer::update(float delta) {


    playerAttack(delta, projectilePool, mySpaceCraft);
    enemyAttack(delta, enemyShipPool);

    collideEnemyAndPlayer(mySpaceCraft, enemyShipPool);
    collideProjectileAndEnemy(projectilePool, enemyShipPool);
}

void GameLayer::moveLeft(Sprite *sprite) {

    int newX = sprite->getPosition().x - 10;
    auto newPos = clampf(newX, sprite->getContentSize().width,
                         winSize.width - sprite->getContentSize().width);
    sprite->runAction(
            EaseCubicActionOut::create(MoveTo::create(0.5, Vec2(newPos, sprite->getPosition().y))));


}

void GameLayer::moveRight(Sprite *sprite) {

    int newX = sprite->getPosition().x + 10;
    auto newPos = clampf(newX, sprite->getContentSize().width,
                         winSize.width - sprite->getContentSize().width);
    sprite->runAction(
            EaseCubicActionOut::create(MoveTo::create(0.5, Vec2(newPos, sprite->getPosition().y))));

}

bool GameLayer::checkBoxCollision(Sprite *box1, Sprite *box2) {

    Rect box1Rect = box1->getBoundingBox();
    Rect box2Rect = box2->getBoundingBox();

    if (box1Rect.intersectsRect(box2Rect)) {
        return true;
    } else {
        return false;
    }
}

void GameLayer::spawmEnemies(int enemyNumber) { // fill enemyShip vector for Object Pooling

    iEnemyCount = enemyNumber;
    for (int i = 0; i < iEnemyCount; ++i) {

        enemyShip = EnemyShip::createEnemy();
        enemyShipPool.pushBack(enemyShip);
        this->addChild(enemyShip);

    }

}

void
GameLayer::spawnProjectiles(int projectileNumber) { // fill projectile vector for Object Pooling
    iProjectileCount = projectileNumber;
    for (int i = 0; i < projectileNumber; ++i) {
        projectile = Projectile::create();
        projectilePool.pushBack(projectile);
        this->addChild(projectile);
    }
}

void GameLayer::collideEnemyAndPlayer(Sprite *player, Vector<EnemyShip *> enemyShipPool) {
    for (EnemyShip *enemyShipRef : enemyShipPool) {//detect if enemyship and player collide

        if (enemyShipRef->IsAttacking() &&  //check if ship is onScene
            checkBoxCollision(player, enemyShipRef)) {
            Director::getInstance()->replaceScene(
                    TransitionFlipY::create(1.0f, MainMenu::createScene()));
        }
    }
}

void GameLayer::collideProjectileAndEnemy(Vector<Projectile *> projectilePool,
                                          Vector<EnemyShip *> enemyShipPool) {
    for (Projectile *myProjectile: projectilePool) { // detect if projectiles and enemyship collide
        for (EnemyShip *enemyShipRef : enemyShipPool) {
            if (enemyShipRef->IsAttacking() && checkBoxCollision(myProjectile, enemyShipRef)) {
                enemyShipRef->hideAndStop();
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/exploison.wav");
                scoreCount++;
                scoreLabel->setString(std::to_string(scoreCount));
            }
        }
    }


}

void GameLayer::playerAttack(float delta, Vector<Projectile *> projectilePool, Sprite *player) {

    projectileTimer += delta;
    if (projectileTimer > 0.5f) {
        auto nextProjectile = projectilePool.at(projectileIndex);
        nextProjectile->shoot(player->getPosition());
        projectileTimer = 0;

        projectileIndex += 1;

        if (projectileIndex >= iProjectileCount) {
            projectileIndex = 0;
        }
    }
}

void GameLayer::enemyAttack(float delta, Vector<EnemyShip *> enemyShipPool) {


    enemyShipTimer += delta;
    if (enemyShipTimer > 5) {
        enemyShipTimer = 0;

        for (int i = 1; i < 8; ++i) {
            auto nextEnemyShip = enemyShipPool.at(enemyShipIndex);
            auto mySize = enemyShip->getContentSize().width;
            nextEnemyShip->attack(
                    Vec2(mySize * i + 15, winSize.height - enemyShip->getContentSize().height));
            enemyShipIndex += 1;
            if (enemyShipIndex >= iEnemyCount) {
                enemyShipIndex = 0;
            }
        }
    }

}