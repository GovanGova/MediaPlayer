//
// Created by G on 5/21/2018.
//

#ifndef SIGNAGE_ELEMENT_H
#define SIGNAGE_ELEMENT_H

#include "Dirty.h"
#include<string>
#include "ScreenManager.h"

// Base class for all asset
// Derive and add functionality
//
class Element{
private:
    int posX, posY, width, height;
    int posZ;
    int alpha;


    //Image, video or another assets which needs time to load data
    bool isReady;


    //int oID=

protected:
    GLfloat* formVertices();
    GLuint verBuffer;
    shared_ptr<Dirty> dirty;
    string assetType="";
    shared_ptr<screenManager> screenMng;

public:
    Element(shared_ptr<screenManager> screenMng);

    void setPosX(int posX);
    void setPosY(int posY);
    void setPosZ(int posZ);

    int getPosX(){ return posX;}
    int getPosY(){ return posY;}
    int getPosZ(){ return posZ;}
    string getAssetType(){return assetType;}
    void setHeight(int h);
    int getHeight(){return height;}

    void setWidth(int w);
    int getWidth(){ return width;}

    void setAlpha(int a);
    int getAlpha(){return alpha;}

    virtual void tick(float t);
    virtual void render()=0;
    virtual ~Element();
    virtual void unload();
};


#endif //SIGNAGE_ELEMENT_H
