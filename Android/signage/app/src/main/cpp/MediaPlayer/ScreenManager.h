//
// Created by G on 5/20/2018.
//

#ifndef SIGNAGE_NATIVE_LIB_H
#define SIGNAGE_NATIVE_LIB_H

#include <iostream>
#include <string>
#include<GLES2/gl2.h>
#include <EGL/egl.h>
#include <memory>
#include <android/native_window.h>
#include "logger.h"
#include "../thirdparty/glm/glm.hpp"
#include "../thirdparty/glm/gtc/matrix_transform.hpp"
#include "../thirdparty/glm/gtc/type_ptr.hpp"

#define LOG_TAG "MediaPlayer"
using namespace std;


//screenManager
class screenManager{

    EGLDisplay _display;
    EGLSurface  _surface;
    EGLContext  _context;

    // android window, supported by NDK r5 and newer
    ANativeWindow* _window;
    glm::mat4 m_mv;

    glm::mat4 m_proj;
    glm::vec3 eyePos;
    GLint width;
    GLint height;
    bool initSuccess;

protected:

    bool initEGL();
    bool initOpenGlES();
    void setUpMatrices();



    glm::vec4 clearColor;
    void setViewPort(GLfloat x, GLfloat y, GLfloat w, GLfloat h);



public:
    screenManager();
    ~screenManager();

    void clearScreen();
    void swapBuffer();
    void init();
    void deInit();
    bool checkES2();
    void setWindow(ANativeWindow *window);
    void setRes(GLint w, GLint h);
    bool isInitedBefore();
    int getWidth() { return width;}
    int getHeight() {return height;}
    void destroy();
    glm::mat4 getModelViewProjection();
    GLuint shapeProgram, textureProgram;
};

#endif //SIGNAGE_NATIVE_LIB_H
