//
// Created by G on 8/11/2018.
//

#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
//#define STBI_MALLOC
//#define STBI_REALLOC
//#define STBI_FREE

#include "../thirdparty/other/stb_image.h"



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
        this->loadTextureData(w,h,(const void*)data, bpp);

        this->setPosX(-this->screenMng->getWidth()/2);
        this->setPosY(-this->screenMng->getHeight()/2);
        this->setWidth(this->screenMng->getWidth());
        this->setHeight(this->screenMng->getHeight());
 //       uint8_t* data=new uint8_t[400*400*4];
    //    glReadPixels(0,0,400,400,GL_RGBA,GL_UNSIGNED_BYTE,data);
      //  loadTextureData(400,400, data);
        free(data);

        bLoadTexture=false;
    }
}
void Image::render(){
    Texture::render();
}
void Image::unload(){

}

Image::~Image(){

}

