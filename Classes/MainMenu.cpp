//
// Created by emin on 15.07.2019.
//

#include "MainMenu.h"
#include "GameLayer.h"

USING_NS_CC;

Scene *MainMenu::createScene() {

    return MainMenu::create();
}

bool MainMenu::init() {
    if (!Scene::init()) {

        return false;
    }

    auto winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    Label* label=Label::createWithTTF("Hyper Spacecraft","fonts/arial.ttf",15);
    label->setPosition(origin.x+winSize.width/2,origin.y+winSize.height/2+50);
    label->setColor(Color3B::GREEN);
    this->addChild(label);



    Label* playButton=Label::createWithTTF("Start","fonts/arial.ttf",12);
    MenuItemLabel* linkLabelMenuItem=MenuItemLabel::create(playButton,CC_CALLBACK_1(MainMenu::startGame,this));
    Menu*menu = Menu::create(linkLabelMenuItem,nullptr);

    menu->setPosition(origin.x+winSize.width/2,origin.y+winSize.height/2-50);
    this->addChild(menu);


return true;
}

void MainMenu::startGame(Ref *pSender) {
   Director::getInstance()->replaceScene(TransitionFlipY::create(1.0f,GameLayer::createScene()));

}