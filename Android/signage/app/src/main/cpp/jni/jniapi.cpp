//
// Created by G on 5/20/2018.
//

#include<jni.h>
#include "jniapi.h"
#include "../MediaPlayer/Shape.h"
#include "../MediaPlayer/Image.h"



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
    //scm->deInit();
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
        player = new Player();
        engine = new Engine(shared_ptr<screenManager>(scm));
        script = new Script(shared_ptr<screenManager>(scm));
        engine->attachScript(shared_ptr<Script>(script));
        player->attachMediaEngine(shared_ptr<Engine>(engine));

        //start rendering thread


        shared_ptr<Shape> shape(new Shape(shared_ptr<screenManager>(scm)));
        script->addAsset(shape);
   }

}

JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_nativeOnResume(JNIEnv *jenv, jobject obj){
    //player->startRenderingThread();
}

JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_nativeOnPause(JNIEnv *jenv, jobject obj){
    player->stopRenderingThread();
}

JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_nativeOnStop(JNIEnv *jenv, jobject obj){
    //delete scm;

    //isActivityStopped=true;
   // if(scm->isInitedBefore()) {
   //     player->stopRenderingThread();
     //   scm->deInit();
    //}

   // delete player;
    //delete engine;
    //delete script;
    LOG_INFO("stop");
}
int count=0;
JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_createShape(JNIEnv *jenv, jobject obj) {
    Shape* shape1=new Shape(shared_ptr<screenManager>(scm));

    shape1->setPosX(count*10);
    shape1->setPosY(count*10);
    count++;
    script->addAsset(shared_ptr<Shape>(shape1));
    shape1= nullptr;
}

JNIEXPORT void JNICALL Java_com_example_g_signage_MainActivity_createTexture(JNIEnv *jenv, jobject obj, jstring filename) {

    Image* shape1 = new Image(shared_ptr<screenManager>(scm));


    shape1->setPosX(count*10);
    shape1->setPosY(count*10);
    shape1->setFilename(std::string(jenv->GetStringUTFChars(filename, 0)));

    count++;
    script->addAsset(shared_ptr<Image>(shape1));
    shape1= nullptr;
}