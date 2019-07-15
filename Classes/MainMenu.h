//
// Created by emin on 15.07.2019.
//

#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"

USING_NS_CC;

class MainMenu : public Scene {


public:
    static Scene*createScene();
    virtual bool init();

    Size *winSize;
    Vec2 *origin;

    CREATE_FUNC(MainMenu);

    void startGame(Ref* pSender);
};


#endif //__MAINMENU_H__
