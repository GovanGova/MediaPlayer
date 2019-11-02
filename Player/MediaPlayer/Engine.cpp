//
// Created by G on 5/29/2018.
//

#include "Engine.h"

std::list<std::shared_ptr<Engine>> Engine::m_engines;

Engine::Engine(std::shared_ptr<screenManager> screen)
    : screenMangr(screen),
      playNow(nullptr),
      playNext(nullptr),
      playPrev(nullptr)
{
}

void Engine::clearScreen()
{
    screenMangr->clearScreen();
}

void Engine::swapScreen()
{
    screenMangr->swapBuffer();
}

void Engine::initScrenManager()
{
    screenMangr->init();
}

void Engine::setRes(GLint w, GLint h)
{
    if (!screenMangr)
    {
        screenMangr->setRes(w, h);
    }
}

void Engine::tick()
{
    if(screenMangr->isSurfaceRestored())
    {
        if (playNow != nullptr)
            playNow->unload();
        screenMangr->clearSurfaceRestored();
    }

    if (playNow != nullptr)
    {
        playNow->tick();
    }
}

void Engine::render()
{
    if (playNow != nullptr)
    {
        playNow->render();
    }
}

void Engine::loadPlayNow()
{
}

void Engine::loadPlayNext()
{
}

void Engine::attachScript(std::shared_ptr<Script> script)
{
    playNow = script;
}

Engine::~Engine()
{
    playNow = playNext = playPrev = nullptr;
}