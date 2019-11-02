//
// Created by G on 5/29/2018.
//
#include "Script.h"



Script::Script(shared_ptr<screenManager> screenMng)
        : screenMng(screenMng)
{
    isStarted = isCompleted =
        isStopped = isPaused = isPlaying = false;
}

void Script::setResX(uint resX){
    m_resX=resX;
}

void Script::setResY(uint resY){
    m_resY=resY;
}


void Script::addAsset(std::shared_ptr<Element> t){
    std::lock_guard<std::mutex> lock(assetLock);
    assetslist.push_back(t);
    //MediaImage* a= new MediaImage(shared_ptr<screenManager>(new screenManager()), "");
}


void Script::tick(){

    std::lock_guard<std::mutex> lock(assetLock);
    for (std::list<shared_ptr<Element>>::iterator it=assetslist.begin(); it != assetslist.end(); ++it)
            it->get()->tick(0.0f);
}

void Script::render() {
    std::lock_guard<std::mutex> lock(assetLock);
    for (std::list<shared_ptr<Element>>::iterator it=assetslist.begin(); it != assetslist.end(); ++it)
        it->get()->render();
}

bool Script::play(){
    return true;
}
bool Script::pause(){
    return true;
}
bool Script::seek(float tSecs){
    return true;
}

bool Script::start() {
    return true;
}

bool Script::reset() {
    return true;
}

bool Script::stop() {
    return true;
}

void Script::unload(){
    std::lock_guard<std::mutex> lock(assetLock);
    for (std::list<shared_ptr<Element>>::iterator it=assetslist.begin(); it != assetslist.end(); ++it) {
        it->get()->unload();
        it->get()->onWindowRestored();
    }
}

Script::~Script(){

}