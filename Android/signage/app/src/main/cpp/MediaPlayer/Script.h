// Script:
// Player to control playing of this script for specified duration
//
// Created by G on 5/29/2018.
//

#ifndef SIGNAGE_SCRIPT_H
#define SIGNAGE_SCRIPT_H

#include <string>
#include <list>
#include "Element.h"
#include <thread>
#include <mutex>

class Script
{

    std::string m_name;
    float m_duration;
    uint m_resX;
    uint m_resY;
    bool isStarted, isCompleted, isStopped;
    bool isPaused, isPlaying;
    std::list<shared_ptr<Element>> assetslist;
    shared_ptr<screenManager> screenMng;
    std::mutex assetLock;

  public:
    Script(shared_ptr<screenManager> screenMng);

    void setName(std::string name) { m_name = name; }
    std::string getName() { return m_name; }
    void setDuration(float duration) { m_duration = duration; };

    void setResX(uint resX);
    uint getResX() { return m_resX; }

    void setResY(uint resY);
    uint getResY() { return m_resY; }

    void tick();
    void render();

    bool start();
    bool play();
    bool pause();
    bool seek(float tSecs);
    bool stop();
    bool reset();

    //assets addition/remove

    void addAsset(std::shared_ptr<Element> t);

    bool removeAsset(int oId);

    void unload();

    ~Script();
};

#endif //SIGNAGE_SCRIPT_H
