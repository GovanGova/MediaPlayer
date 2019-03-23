//
// Created by G on 8/11/2018.
//

#include "Image.h"
//#define STB_IMAGE_IMPLEMENTATION
//#define STBI_MALLOC
//#define STBI_REALLOC
//#define STBI_FREE

#include "stb/stb_image.h"



Image::Image(shared_ptr<screenManager> scm):
        Texture(scm),
        filename(""),
        bLoadTexture(false)
{

}

void Image::setFilename(std::string file_name){
    filename=file_name;
    bLoadTexture=true;
}
void Image::tick(float tSecs){

   Texture::tick(tSecs);

    if(bLoadTexture==true){

        int w, h, bpp;
        unsigned char* data= stbi_load(filename.c_str(), &w, &h, &bpp,0);
        loadTextureData(w,h,(const void*)data, bpp);

        //setPosX(m_screenMng->getWidth()/2);
        //setPosY(m_screenMng->getHeight()/2);
       // setWidth(w);
        //setHeight(h);
        free(data);

        bLoadTexture=false;
    }
}
void Image::render(){
    Texture::render();
}
void Image::unload(){
    Texture::unload();
}

Image::~Image(){

}

