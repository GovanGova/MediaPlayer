//
// Created by G on 5/29/2018.
//

#include "Texture.h"


Texture::Texture(shared_ptr<screenManager> screenMng)
        : Element(screenMng)
{

}

void Texture::createTexture() {
    if (glIsTexture(texture) == GL_FALSE)
        glGenTextures(1, &texture);

    //texture coordinates
    GLfloat texCord[]={
            0,1,
            1,1,
            1,0,
            0,0
    };

    if(!glIsBuffer(texBufObj)) {
        glGenBuffers(1, &texBufObj);
        glBindBuffer(GL_ARRAY_BUFFER, texBufObj);
        glBufferData(GL_ARRAY_BUFFER,sizeof(texCord),texCord,GL_DYNAMIC_DRAW);
    }
}
void Texture::loadTextureData(int w,int h, const void* data, int bpp){
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if(bpp==4)
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    else if(bpp==3)
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::tick(float tSecs){
    if(dirty->getDirtyFlag()==DF_ALL){
        createTexture();
        //uint8_t* data=new uint8_t[400*400*4];
        //glReadPixels(0,0,400,400,GL_RGBA,GL_UNSIGNED_BYTE,data);
        //loadTextureData(400,400, data);
        //delete data;
    }
    Element::tick(tSecs);
}

void Texture::render()
{
    glUseProgram(screenMng->textureProgram);

    glBindBuffer(GL_ARRAY_BUFFER, verBuffer);
    GLuint vertexLoc = glGetAttribLocation(screenMng->textureProgram,"vVertex");
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc,3,GL_FLOAT,GL_FALSE,0,NULL);

    glBindBuffer(GL_ARRAY_BUFFER,texBufObj);
    GLuint texCoorLoc = glGetAttribLocation(screenMng->textureProgram,"vTexture");
    glEnableVertexAttribArray(texCoorLoc);
    glVertexAttribPointer(texCoorLoc,2,GL_FLOAT,GL_FALSE,0,NULL);

    //glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,texture);
    GLuint colorLoc = glGetUniformLocation(screenMng->textureProgram,"sampler");
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(colorLoc,0);

    GLuint mvpLoc = glGetUniformLocation(screenMng->textureProgram,"mvpMatrix");
    glUniformMatrix4fv(mvpLoc,1,GL_FALSE, glm::value_ptr(screenMng->getModelViewProjection()));

    glDrawArrays(GL_TRIANGLE_FAN,0,4);
    glDisableVertexAttribArray(vertexLoc);
}

Texture::~Texture(){

}