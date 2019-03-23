//
// Created by G on 5/20/2018.
//

#ifndef SIGNAGE_NATIVE_LIB_H
#define SIGNAGE_NATIVE_LIB_H

#include "Base.h"
#include<random>

#define LOG_TAG "MediaPlayer"

 
using namespace std;

extern std::mt19937 range;

//screenManager
class screenManager
{

#ifdef __ANDROID__
    EGLDisplay _display;
    EGLSurface _surface;
    EGLContext _context;

    // android window, supported by NDK r5 and newer

    ANativeWindow *_window;
#endif

    glm::mat4 m_mv;

    glm::mat4 m_proj;
    glm::vec3 eyePos;
    GLint width;
    GLint height;
    bool initSuccess;
    bool m_bSurfaceResotred{false};

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

    void setRes(GLint w, GLint h);
    bool isInitedBefore();
    int getWidth() { return width; }
    int getHeight() { return height; }
    void destroy();
    bool isSurfaceRestored(){ return m_bSurfaceResotred;}
    void clearSurfaceRestored(){m_bSurfaceResotred = false;}

#ifdef __ANDROID__
    void setWindow(ANativeWindow *window);
#endif
    glm::mat4 getModelViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getModelViewProjection();
    GLuint shapeProgram, textureProgram, ptSpritePgm;
};

#ifndef __ANDROID__
inline void LOG_INFO(const char* data){
  cout<<data<<endl;
}
#endif

#endif //SIGNAGE_NATIVE_LIB_H
