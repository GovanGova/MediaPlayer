//
// Created by G on 5/29/2018.
//

#ifndef SIGNAGE_ENGINE_H
#define SIGNAGE_ENGINE_H

#include <list>
#include "ScreenManager.h"
#include "Script.h"

class Engine
{
    int resX, resY;
    shared_ptr<screenManager> screenMangr;
    shared_ptr<Script> playNow, playNext, playPrev;

  public:
    Engine(shared_ptr<screenManager> screen);
    ~Engine();
    void clearScreen();
    void initScrenManager();
    void swapScreen();
    void tick();
    void render();
    void setRes(GLint w, GLint h);

    void loadPlayNow();
    void loadPlayNext();
    void attachScript(shared_ptr<Script> script);
    static list<shared_ptr<Engine>> m_engines;
};

#endif //SIGNAGE_ENGINE_H
