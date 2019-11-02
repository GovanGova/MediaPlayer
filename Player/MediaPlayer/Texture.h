//
// Created by G on 5/29/2018.
//

#pragma once


#include "Element.h"
class Texture : public Element
{
  protected:
    void createTexture();
    void loadTextureData(int w, int h, const void *data, int bpp);
    virtual void formTextureCoordinates(std::vector<GLfloat>& tetureCoord);
    GLuint m_textureID=0;
    GLuint m_textureBuf=0;
    
  public:
    Texture(shared_ptr<screenManager> screenMng);
    static int loadTextureFile(string filename);
    void tick(float tSecs) override;
    void render() override;
    void unload() override;

    ~Texture();
};