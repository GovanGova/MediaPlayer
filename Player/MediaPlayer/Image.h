//
// Created by G on 8/11/2018.
//

#pragma once

#include "Texture.h"


class Image: public Texture{
    std::string filename;
    bool bLoadTexture{false};
    bool m_bShowOriginal{false};
public:
    Image(shared_ptr<screenManager> scm);

    void setFilename(std::string file_name);
    void showOriginal(bool isOriginal);
    void tick(float tSecs) override;
    void render() override;
    void unload() override;

    ~Image();
};