//
// Created by G on 5/29/2018.
//

#include "Texture.h"
//#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
//#endif
#include "stb/stb_image.h"

Texture::Texture(shared_ptr<screenManager> screenMng)
    : Element(screenMng)
{
}

void Texture::formTextureCoordinates(std::vector<GLfloat> &texCoord)
{
    texCoord.push_back(0.0);
    texCoord.push_back(1.0);
    texCoord.push_back(1.0);
    texCoord.push_back(1.0);
    texCoord.push_back(1.0);
    texCoord.push_back(0.0);
    texCoord.push_back(0.0);
    texCoord.push_back(0.0);
}

void Texture::createTexture()
{
    if (glIsTexture(m_textureID) == GL_FALSE)
        glGenTextures(1, &m_textureID);

    if (!glIsBuffer(m_textureBuf))
    {
        glGenBuffers(1, &m_textureBuf);
        glBindBuffer(GL_ARRAY_BUFFER, m_textureBuf);
        std::vector<GLfloat> texCoord;
        formTextureCoordinates(texCoord);
        auto size = texCoord.size();
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*texCoord.size(), texCoord.data(), GL_DYNAMIC_DRAW);
    }
}
void Texture::loadTextureData(int w, int h, const void *data, int bpp)
{
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if (bpp == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else if (bpp == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else if (bpp == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::tick(float tSecs)
{
    if (m_dirty->getDirtyFlag() == DF_ALL)
    {
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
    glUseProgram(m_screenMng->textureProgram);

    glBindBuffer(GL_ARRAY_BUFFER, m_verBuffer);
    GLuint vertexLoc = glGetAttribLocation(m_screenMng->textureProgram, "vVertex");
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, m_textureBuf);
    GLuint texCoorLoc = glGetAttribLocation(m_screenMng->textureProgram, "vTexture");
    glEnableVertexAttribArray(texCoorLoc);
    glVertexAttribPointer(texCoorLoc, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    //glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    GLuint samplerLoc = glGetUniformLocation(m_screenMng->textureProgram, "sampler");
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(samplerLoc, 0);

    GLuint colorLoc = glGetUniformLocation(m_screenMng->textureProgram, "vColor");
    glUniform4f(colorLoc, m_r, m_g, m_b, m_a);

    auto modelView = glm::translate(m_screenMng->getModelViewMatrix(), getGravity());
    auto mvp = m_screenMng->getProjectionMatrix() * modelView; // m_screenMng->getModelViewMatrix();
    GLuint mvpLoc = glGetUniformLocation(m_screenMng->textureProgram, "mvpMatrix");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableVertexAttribArray(vertexLoc);
    glUseProgram(0);
}

void Texture::unload()
{
    glDeleteTextures(1, &m_textureID);
    glDeleteBuffers(1, &m_textureBuf);
    Element::unload();
}
Texture::~Texture()
{
}

 int Texture::loadTextureFile(string filename)

{
    int w, h, bpp;
    GLuint texID;
    unsigned char *data = stbi_load(filename.c_str(), &w, &h, &bpp, 0);
    if(data==nullptr)
        return -1;
        
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if (bpp == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else if (bpp == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else if (bpp == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;
}