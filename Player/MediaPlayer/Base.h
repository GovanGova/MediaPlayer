#pragma once

#ifdef __ANDROID__
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "logger.h"
#include <android/native_window.h>
#else
#include <GL/glew.h> //g++ test.cpp  -Wall -o triangle -lGLEW
#include <GL/gl.h>   // -lGL
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <string>
#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//#define STB_IMAGE_IMPLEMENTATION
//#define STBI_MALLOC
//#define STBI_REALLOC
//#define STBI_FREE
//#include "stb/stb_image.h"

// Freetype font library
//
#include "freetype/include/freetype2/ft2build.h"
#include "freetype/include/freetype2/freetype/ftbitmap.h"

#include FT_FREETYPE_H