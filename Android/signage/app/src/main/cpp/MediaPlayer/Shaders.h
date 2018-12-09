//
// Created by G on 6/30/2018.
//

#ifndef SIGNAGE_SHADERS_H
#define SIGNAGE_SHADERS_H

#include<GLES2/gl2.h>
#include <vector>
const char* shapeVp =
                        "attribute vec3 vVertex; \n"
                        "uniform mat4 mvpMatrix; \n"

                        "void main(void){\n"
                        "gl_Position = mvpMatrix*vec4(vVertex,1);\n"
                        "}";

const char* shapeFp =
                        "precision mediump float;"
                        "uniform vec4 vColor;\n"

                        "void main(void){"
                        "gl_FragColor = vColor;"
                        "}";

const char* textureVp =
                        "attribute vec3 vVertex; \n"
                        "attribute vec2 vTexture; \n"
                        "uniform mat4 mvpMatrix; \n"
                        "varying vec2 vTex;\n"
                        "void main(void){\n"
                            "vTex=vTexture;\n"
                            "gl_Position = mvpMatrix*vec4(vVertex,1);\n"
                        "}";

const char* textureFp =
                        "precision mediump float;"
                        "uniform sampler2D sampler;"
                        "varying vec2 vTex;"
                        "void main(void){"
                            "gl_FragColor = texture2D(sampler, vTex);"
                        "}";


static const char *szIdentityShaderVP = "attribute vec3 vVertex;"
        "void main(void) "
        "{ gl_Position = vec4(vVertex,1); "
        "}";

static const char *szIdentityShaderFP =

        "precision mediump float;"

        "uniform vec4 vColor;"
                "void main(void) "
                "{ gl_FragColor = vColor;"
                "}";



bool compileAndLinkShader(GLuint* programId, const char* vertexPgm, const char* fragmentPgm){

    GLuint vertShader=glCreateShader(GL_VERTEX_SHADER);

    GLchar *fsStringPtr[1];

    fsStringPtr[0] = (GLchar *)vertexPgm;
    glShaderSource(vertShader, 1, (const GLchar **)fsStringPtr, NULL);


    //compile vertex shader
    glCompileShader(vertShader);
    GLint isCompiled;
    glGetShaderiv(vertShader,GL_COMPILE_STATUS,&isCompiled);
    if(isCompiled == GL_FALSE){
        GLint maxLength = 0;
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        GLchar* infoLog= new GLchar(maxLength);
        glGetShaderInfoLog(vertShader, maxLength, &maxLength, infoLog);

        // We don't need the shader anymore.
        glDeleteShader(vertShader);
        delete infoLog;
        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        return false;
    }

    GLuint fragShader= glCreateShader(GL_FRAGMENT_SHADER);

    //GLchar *fsStringPtr[1];

    fsStringPtr[0] = (GLchar *)fragmentPgm;
    glShaderSource(fragShader, 1, (const GLchar **)fsStringPtr, NULL);

    //glShaderSource(fragShader,1,(const GLchar * const *)shapeFp, NULL);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader,GL_COMPILE_STATUS,&isCompiled);
    if(isCompiled == GL_FALSE){
        GLint maxLength = 0;
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        GLchar* infoLog= new GLchar(maxLength);
        glGetShaderInfoLog(fragShader, maxLength, &maxLength, infoLog);

        // We don't need the shader anymore.
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        delete infoLog;
        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        return false;
    }

    //create program
    GLuint pgm = glCreateProgram();

    //attach program
    glAttachShader(pgm, vertShader);
    glAttachShader(pgm, fragShader);

    //link program
    glLinkProgram(pgm);
    glGetProgramiv(pgm,GL_LINK_STATUS, &isCompiled);

    // Detach and delete the shader objects
    glDetachShader(pgm, vertShader);
    glDeleteShader(vertShader);

    glDetachShader(pgm, fragShader);
    glDeleteShader(fragShader);

    if(isCompiled==GL_FALSE){
        GLint maxLength = 0;
        glGetProgramiv(pgm,GL_INFO_LOG_LENGTH,&maxLength);

        // The maxLength includes the NULL character
        char* infoLog=new char(maxLength);
        glGetProgramInfoLog(pgm, maxLength, &maxLength, infoLog);
    }
    *programId=pgm;
    return true;
}


#endif //SIGNAGE_SHADERS_H
