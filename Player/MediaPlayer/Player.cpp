//
// Created by G on 5/29/2018.
//

#include "Player.h"

Player::Player() : isStopped(false),
                   isStarted(false)
{
}

void Player::attachMediaEngine(std::shared_ptr<Engine> engine)
{
    Engine::m_engines.push_back(engine);
}

void Player::render()
{
    bool bRun = true;
    //while(bRun){
    //std::cout<<"rneder"<<std::endl;
    for (std::list<std::shared_ptr<Engine>>::iterator it = Engine::m_engines.begin(); it != Engine::m_engines.end(); it++)
    {
        it->get()->initScrenManager();
        // glClear(GL_COLOR_BUFFER_BIT);
        // glEnable(GL_SCISSOR_TEST);
        //std::cout<<"engine";
        //// glScissor(100,100,400, 400);
        // glClearColor(0.0f,1.0f,0.0f,1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);

        //glScissor(300,300,400, 400);
        //glClearColor(1.0f,0.0f,0.0f,1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);

        it->get()->clearScreen();
        

        it->get()->tick();
        it->get()->render();
        it->get()->swapScreen();
    }
    // std::unique_lock<std::mutex> lck(lock);
    //lck.lock();
    //std::cout<<"finshed"<<std::endl;
    bRun = !isStopped;
    //}
    //LOG_INFO("Exiting thread");
}
void Player::startRenderingThread(){
    if(!isStarted) {
        std::thread temp(&Player::render, this);
        isStopped = false;
        m_rThread = std::move(temp);
        //m_rThread.start();
        m_rThread.detach();
        isStarted = true;
    }
}
void Player::stopRenderingThread()
{
    //delete m_rThread;
    std::lock_guard<std::mutex> lck(lock);
    //lck.lock();
    LOG_INFO("Stopping thread");
    isStopped=true;
    isStarted=false;
}

Player::~Player()
{
    Engine::m_engines.clear();
}