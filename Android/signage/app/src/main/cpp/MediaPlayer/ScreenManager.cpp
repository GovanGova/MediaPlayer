
#include "ScreenManager.h"
#include "Shaders.h"

using namespace std;

screenManager::screenManager() {
    _display = EGL_NO_DISPLAY;
    _surface = EGL_NO_SURFACE;
    _context = EGL_NO_CONTEXT;
    eyePos = glm::vec3(10.0f);
    clearColor= glm::vec4(0,0,0,1);
}

bool screenManager::initEGL(){
    const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    EGLDisplay display;
    EGLConfig config;
    EGLint numConfigs;
    EGLint format;
    EGLSurface surface;
    EGLContext context;
    EGLint width;
    EGLint height;
    GLfloat ratio;

    LOG_INFO("Initializing context");

    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        LOG_ERROR("eglGetDisplay() returned error %d", eglGetError());
        return false;
    }
    if (!eglInitialize(display, 0, 0)) {
        LOG_ERROR("eglInitialize() returned error %d", eglGetError());
        return false;
    }

    if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs)) {
        LOG_ERROR("eglChooseConfig() returned error %d", eglGetError());
        destroy();
        return false;
    }

    if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format)) {
        LOG_ERROR("eglGetConfigAttrib() returned error %d", eglGetError());
        destroy();
        return false;
    }

    ANativeWindow_setBuffersGeometry(_window, 0, 0, format);

    if (!(surface = eglCreateWindowSurface(display, config, _window, 0))) {
        LOG_ERROR("eglCreateWindowSurface() returned error %d", eglGetError());
        destroy();
        return false;
    }

    const EGLint conAttribs[] = {

            EGL_CONTEXT_CLIENT_VERSION,2,
            EGL_NONE

    };

    if (!(context = eglCreateContext(display, config, 0, conAttribs))) {
        EGLint  error=eglGetError();
        LOG_ERROR("eglCreateContext() returned error %d", eglGetError());
        destroy();
        return false;
    }

    if (!eglMakeCurrent(display, surface, surface, context)) {
        LOG_ERROR("eglMakeCurrent() returned error %d", eglGetError());
        destroy();
        return false;
    }

    if (!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
        !eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
        LOG_ERROR("eglQuerySurface() returned error %d", eglGetError());
        destroy();
        return false;
    }
    this->width=width;
    this->height=height;

    _display = display;
    _surface = surface;
    _context = context;

    LOG_INFO("Initialition is successful");
    return true;
}
bool screenManager::initOpenGlES(){
    LOG_INFO("Initializing OpenGL context");

    glClearColor(clearColor.r, clearColor.g,clearColor.b, clearColor.a);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    return true;
}

void screenManager::setViewPort(GLfloat x, GLfloat y, GLfloat w, GLfloat h){
    glViewport(x,y,w,h);
}

void screenManager:: clearScreen(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void screenManager::init(){
    if(!initSuccess) {
        if (initEGL()) {
            initOpenGlES();
            setUpMatrices();
            //clearScreen();
            compileAndLinkShader(&shapeProgram,shapeVp, shapeFp);
            compileAndLinkShader(&textureProgram,textureVp, textureFp);

            initSuccess = true;
            //swapBuffer();
        }
    }
}

void screenManager::swapBuffer(){
    if(initSuccess){

        if (!eglSwapBuffers(_display, _surface)) {
            LOG_ERROR("eglSwapBuffers() returned error %d", eglGetError());
        }
    }
}
void screenManager::setRes(GLint w, GLint h){
   // handle window here
}

bool screenManager::checkES2(){
    return true;
}

bool screenManager::isInitedBefore(){
    return initSuccess;
}

void screenManager::setUpMatrices(){
    //Load identity matrix
    m_mv=glm::mat4(1.0);

    //Translate to eye matrix
    glm::translate(m_mv, eyePos);

    // set viewport
    setViewPort(0,0,width,height);

    //m_proj = glm::perspective(0.785398f,(float)width/height,0.0f, 1000.0f);
    m_proj = glm::ortho((float)-width/2, (float)width/2, (float)-height/2, (float)height/2, -100.0f, 100.0f);
    //m_proj=glm::mat4(1.0);
    //m_proj= glm::ortho(-width/2, width/2, -height/2, height/2, -100, 100);
}

glm::mat4 screenManager::getModelViewProjection(){
    return m_mv*m_proj;
}

void screenManager::setWindow(ANativeWindow *window){
    _window=window;
}

// destroys display, surface and contex
//
void screenManager::destroy(){
    LOG_INFO("Destroying context");

    eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(_display, _context);
    eglDestroySurface(_display, _surface);
    eglTerminate(_display);

    _display = EGL_NO_DISPLAY;
    _surface = EGL_NO_SURFACE;
    _context = EGL_NO_CONTEXT;
}

screenManager::~screenManager(){
    destroy();
}

void screenManager::deInit(){
    initSuccess=false;
    destroy();
}

