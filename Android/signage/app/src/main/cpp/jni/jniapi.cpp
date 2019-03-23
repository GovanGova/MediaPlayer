//
// Created by G on 5/20/2018.
//

#include<jni.h>
#include "jniapi.h"
#include "../MediaPlayer/Shape.h"
#include "../MediaPlayer/Image.h"
#include "../MediaPlayer/PointSprite.h"



#include <android/native_window_jni.h>

screenManager* scm= nullptr;
Player* player= nullptr;
Script* script= nullptr;
Engine* engine= nullptr;
bool isActivityStopped=false;

JNIEXPORT jstring JNICALL Java_com_example_g_signage_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject obj) {
    std::string str="hello";
    return env->NewStringUTF(str.c_str());
}

JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_setSurface(
        JNIEnv *jenv, jobject obj, jobject surface, jobject format, jobject w, jobject h) {
    LOG_INFO("setSurface");

    if(isActivityStopped)
    {
        LOG_INFO("Activity is in stop mode");
        return;
    }

    if(scm->isInitedBefore()) {
        player->stopRenderingThread();
        scm->deInit();
    }

    scm->setWindow(ANativeWindow_fromSurface(jenv, surface));
    //scm->init();
    player->startRenderingThread();

}

JNIEXPORT void JNICALL
Java_com_example_g_signage_MainActivity_nativeOnSurfaceDestroyed(JNIEnv *jenv, jobject obj){
    LOG_INFO("surface destroyed");
    player->stopRenderingThread();
    scm->deInit();

}

JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_nativeOnStart(JNIEnv *jenv, jobject obj){
    LOG_INFO("start");
    isActivityStopped=false;
    if(scm== nullptr) {
        scm = new screenManager();
    }

    if(player==nullptr) {
        LOG_INFO("Player is empty");
        player = new Player();
        engine = new Engine(shared_ptr<screenManager>(scm));
        script = new Script(shared_ptr<screenManager>(scm));
        engine->attachScript(shared_ptr<Script>(script));
        player->attachMediaEngine(shared_ptr<Engine>(engine));

        shared_ptr<Shape> shape(new Shape(shared_ptr<screenManager>(scm)));
        script->addAsset(shape);
   }

}

JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_nativeOnResume(JNIEnv *jenv, jobject obj){
    //player->startRenderingThread();
    isActivityStopped=true;
    LOG_INFO("Resumed");
}

JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_nativeOnPause(JNIEnv *jenv, jobject obj){
    //player->stopRenderingThread();
    LOG_INFO("paused");
}

JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_nativeOnStop(JNIEnv *jenv, jobject obj){
    isActivityStopped=true;
    LOG_INFO("stop");
}

JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_nativeOnDesroy(JNIEnv *jenv, jobject obj){

    if(scm->isInitedBefore()) {
        player->stopRenderingThread();
        scm->deInit();
    }

    delete player;
    delete engine;
    delete script;
    delete scm;
    LOG_INFO("Destroying media player");
}
int assetCount=0;
JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_createShape(JNIEnv *jenv, jobject obj) {
    Shape* shape1=new Shape(shared_ptr<screenManager>(scm));

    shape1->setPosX(assetCount*10);
    shape1->setPosY(assetCount*10);
    assetCount++;
    script->addAsset(shared_ptr<Shape>(shape1));
    shape1= nullptr;
}

JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_createTexture(JNIEnv *jenv, jobject obj, jstring filename) {

    PointSprite* point = new PointSprite(shared_ptr<screenManager>(scm), 100);

    point->setPosX(-(float)(scm->getWidth() / 2));
    point->setPosY(-(float)(scm->getHeight() / 2));
    point->setPosZ(0);
    point->setWidth((float)scm->getWidth());
    point->setBreadth(10);
    point->setHeight((float)scm->getHeight());
    point->setColor(1.0, 1.0, 1.0, 0.9);
    point->setFilename(std::string(jenv->GetStringUTFChars(filename, 0)));
//
//    Image* point = new Image(shared_ptr<screenManager>(scm));
//    point->setPosX(assetCount*10);
//    point->setPosY(assetCount*10);
//    point->setWidth(500);
//    point->setHeight(500);
//    point->setFilename(std::string(jenv->GetStringUTFChars(filename, 0)));

    assetCount++;
    script->addAsset(shared_ptr<PointSprite>(point));
    point= nullptr;
}