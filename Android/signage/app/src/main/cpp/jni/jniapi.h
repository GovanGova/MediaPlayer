//
// Created by G on 5/20/2018.
//

#ifndef SIGNAGE_JNI_H
#define SIGNAGE_JNI_H

#include "../MediaPlayer/ScreenManager.h"
#include "../MediaPlayer/Player.h"
#include "../MediaPlayer/Engine.h"
#include "../MediaPlayer/Script.h"
#include "../MediaPlayer/Texture.h"
#include "../MediaPlayer/Image.h"

extern "C" {
JNIEXPORT void JNICALL
Java_com_example_g_signage_MainActivity_nativeOnStart(JNIEnv *jenv, jobject obj);
JNIEXPORT void JNICALL
Java_com_example_g_signage_MainActivity_nativeOnResume(JNIEnv *jenv, jobject obj);
JNIEXPORT void JNICALL
Java_com_example_g_signage_MainActivity_nativeOnPause(JNIEnv *jenv, jobject obj);
JNIEXPORT void JNICALL
Java_com_example_g_signage_MainActivity_nativeOnStop(JNIEnv *jenv, jobject obj);

JNIEXPORT jstring JNICALL
Java_com_example_g_signage_MainActivity_stringFromJNI(JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL
Java_com_example_g_signage_MainActivity_setSurface(JNIEnv *env, jobject obj, jobject surface, jobject format,
                                                   jobject w, jobject h);
JNIEXPORT void JNICALL
Java_com_example_g_signage_MainActivity_nativeOnSurfaceDestroyed(JNIEnv *jenv, jobject obj);
JNIEXPORT void JNICALL
Java_com_example_g_signage_MainActivity_createShape(JNIEnv *jenv, jobject obj);

JNIEXPORT void JNICALL
Java_com_example_g_signage_MainActivity_createTexture(JNIEnv *jenv, jobject obj, jstring filename);

};

#endif //SIGNAGE_JNI_H
