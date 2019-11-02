//
// Created by G on 5/29/2018.
//

#pragma once

#include <thread>
#include "Engine.h"

// Pending closing threads
//

class Player
{

    std::thread m_rThread;
    bool isStopped, isStarted;
    std::mutex lock;

  protected:
  public:
    Player();
    Player *operator()();
    //thread function

    void attachMediaEngine(std::shared_ptr<Engine> engine);

    void startRenderingThread();
    void stopRenderingThread();
    void render();
    ~Player();
};

