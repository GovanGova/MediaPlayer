//
// Created by G on 5/29/2018.
//

#ifndef SIGNAGE_TEXTURE_H
#define SIGNAGE_TEXTURE_H

#include "Element.h"
class Texture : public Element
{
    GLuint texture;
    GLuint texBufObj;

protected:
    void createTexture();
    void loadTextureData(int w,int h, const void* data, int bpp);

public:
    Texture(shared_ptr<screenManager> screenMng);

    virtual void tick(float tSecs) ;
    virtual void render() ;
    virtual void unload() {}

    ~Texture();
};


#endif //SIGNAGE_TEXTURE_H
