//
// Created by G on 8/11/2018.
//

#ifndef SIGNAGE_IMAGE_H
#define SIGNAGE_IMAGE_H

#include "Texture.h"


class Image: public Texture{
    std::string filename;
    bool bLoadTexture;
public:
    Image(shared_ptr<screenManager> scm);

    void setFilename(std::string file_name);
    virtual void tick(float tSecs);
    virtual void render();
    virtual void unload();

    ~Image();
};
#endif //SIGNAGE_IMAGE_H
