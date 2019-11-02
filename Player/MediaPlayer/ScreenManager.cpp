
#include "ScreenManager.h"
#include "Shaders.h"

using namespace std;

std::mt19937 range;
uint32_t seed;
screenManager::screenManager()
{
#ifdef __ANDROID__
    _display = EGL_NO_DISPLAY;
    _surface = EGL_NO_SURFACE;
    _context = EGL_NO_CONTEXT;
#endif
    clearColor = glm::vec4(0.0, 0.0, 0.0, 900.0);
    camera = std::shared_ptr<Camera>(new Camera());
}

bool screenManager::initEGL()
{
#ifdef __ANDROID__

    const EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE};
    EGLDisplay display;
    EGLConfig config;
    EGLint numConfigs;
    EGLint format;
    EGLSurface surface;
    EGLContext context;
    EGLint width;
    EGLint height;
    GLfloat ratio;

    //LOG_INFO("Initializing context");

    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY)
    {
        LOG_ERROR("eglGetDisplay() returned error %d", eglGetError());
        return false;
    }
    if (!eglInitialize(display, 0, 0))
    {
        LOG_ERROR("eglInitialize() returned error %d", eglGetError());
        return false;
    }

    if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs))
    {
        LOG_ERROR("eglChooseConfig() returned error %d", eglGetError());
        destroy();
        return false;
    }

    if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format))
    {
        LOG_ERROR("eglGetConfigAttrib() returned error %d", eglGetError());
        destroy();
        return false;
    }

    ANativeWindow_setBuffersGeometry(_window, 0, 0, format);

    if (!(surface = eglCreateWindowSurface(display, config, _window, 0)))
    {
        LOG_ERROR("eglCreateWindowSurface() returned error %d", eglGetError());
        //destroy();
        return false;
    }

    const EGLint conAttribs[] = {

        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE

    };

    if (!(context = eglCreateContext(display, config, 0, conAttribs)))
    {
        EGLint error = eglGetError();
        LOG_ERROR("eglCreateContext() returned error %d", eglGetError());
        destroy();
        return false;
    }

    if (!eglMakeCurrent(display, surface, surface, context))
    {
        LOG_ERROR("eglMakeCurrent() returned error %d", eglGetError());
        destroy();
        return false;
    }

    if (!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
        !eglQuerySurface(display, surface, EGL_HEIGHT, &height))
    {
        LOG_ERROR("eglQuerySurface() returned error %d", eglGetError());
        destroy();
        return false;
    }
    this->width = width;
    this->height = height;

    _display = display;
    _surface = surface;
    _context = context;

    m_bSurfaceResotred = true;

#endif
    range.seed(seed);
    //LOG_INFO("Initialition is successful");
    return true;
}
bool screenManager::initOpenGlES()
{
    //LOG_INFO("Initializing OpenGL context");

    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    return true;
}

void screenManager::setViewPort(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
    glViewport(x, y, w, h);
}

void screenManager::clearScreen()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void screenManager::init()
{
    if (!initSuccess && initEGL())
    {

        initOpenGlES();

        setUpMatrices();
        //clearScreen();
        compileAndLinkShader(&shapeProgram, shapeVp, shapeFp);
        compileAndLinkShader(&ptSpritePgm, ptSpriteVp, ptSpriteFp);
        compileAndLinkShader(&textureProgram, textureVp, textureFp);
        compileAndLinkShader(&textProgram, textVp, textFp);
        // Initialize freetype font library
        //
        initFreeType();

        initSuccess = true;
        //swapBuffer();
    }
}

void screenManager::swapBuffer()
{
    if (initSuccess)
    {

#ifdef __ANDROID__
        if (!eglSwapBuffers(_display, _surface))
        {
            LOG_ERROR("eglSwapBuffers() returned error %d", eglGetError());
        }
#endif
    }
}
void screenManager::setRes(GLint w, GLint h)
{
    // handle window here
    this->width = w;
    this->height = h;

    if (isInitedBefore())
        setUpMatrices();
}

bool screenManager::checkES2()
{
    return true;
}

bool screenManager::isInitedBefore()
{
    return initSuccess;
}

void screenManager::initFreeType()
{
    if (FT_Init_FreeType(&ft))
    {
        fprintf(stderr, "Could not init freetype library\n");
    }
}

void screenManager::closeFreeType()
{
    if (FT_Done_FreeType(ft))
    {
        fprintf(stderr, "Could not init freetype library\n");
    }
}

void screenManager::setUpMatrices()
{
    //Load identity matrix
    m_mv = glm::mat4(1.0);

    //Translate to eye matrix
    //m_mv = glm::translate(m_mv, eyePos);
    //m_mv = glm::rotate(m_mv, 3.14f/4, glm::vec3(0,1,0));
    //m_mv= glm::lookAt(glm::vec3(0.0,0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    m_mv = camera->getViewMat();

    // set viewport
    setViewPort(0, 0, width, height);

    m_proj = glm::perspective(1.5f, (float)width / (float)height, 0.1f, 1000.0f);
    //m_proj = glm::ortho((float)-width / 2, (float)width / 2, (float)-height / 2, (float)height / 2, 0.0f, 1000.0f);
}

glm::mat4 screenManager::getModelViewMatrix()
{
    return m_mv;
}

glm::mat4 screenManager::getProjectionMatrix()
{
    return m_proj;
}

glm::mat4 screenManager::getModelViewProjection()
{
    return m_proj * m_mv;
}

#ifdef __ANDROID__
void screenManager::setWindow(ANativeWindow *window)
{
    _window = window;
    initSuccess = false;
}
#endif

// destroys display, surface and contex
//
void screenManager::destroy()
{
    //LOG_INFO("Destroying context");

#ifdef __ANDROID__
    eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(_display, _context);
    eglDestroySurface(_display, _surface);
    eglTerminate(_display);

    _display = EGL_NO_DISPLAY;
    _surface = EGL_NO_SURFACE;
    _context = EGL_NO_CONTEXT;
#endif
    closeFreeType();
}

screenManager::~screenManager()
{
    destroy();
}

void screenManager::deInit()
{
    initSuccess = false;
    destroy();
}
