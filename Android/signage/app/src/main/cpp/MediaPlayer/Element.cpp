//
// Created by G on 5/21/2018.
//

#include "Element.h"

// Element class member function
//
Element::Element(shared_ptr<screenManager> screenMng)
        : screenMng(screenMng)
{
    posX=posY=0;
    width=height=200;
    posZ=-99;
    isReady=false;
    dirty = shared_ptr<Dirty>(new Dirty());
}

void Element::setPosX(int x){
    if(posX!=x) {
        posX = x;
        dirty->setDirty(DF_XY);
    }
}

void Element::setPosY(int y){
    if(posY!=y) {
        posY = y;
        dirty->setDirty(DF_XY);
    }
}

void  Element::setPosZ(int z){
    if(posZ!= z) {
        posY = z;
        dirty->setDirty(DF_XY);
    }
}
void Element::setHeight(int h){
    if(height!=h) {
        height = h;
        dirty->setDirty(DF_WH);
    }
}

void Element::setWidth(int w){
    if(width != w) {
        width = w;
        dirty->setDirty(DF_WH);
    }
}

void Element::setAlpha(int a){
    alpha=a;
}

GLfloat* Element::formVertices(){

    GLfloat x=posX, y=posY, z=posZ;
    GLfloat* vertices =new GLfloat[12]{
                        x, y+height, z,
                        x+width, y, z,
                        x+width, y+height, z,
                        x, y,z,


    };


    return vertices;
}

void Element::tick(float tSecs) {

    // Create vertex buffer
    //
    if(dirty->getDirtyFlag()==DF_ALL){
        glGenBuffers(1, &verBuffer);
    }
    if(dirty->getDirtyFlag()!= DF_NONE) {
        if(dirty->getDirtyFlag()&DF_XY || dirty->getDirtyFlag() & DF_WH)
        {
            GLfloat x=posX, y=posY, z=posZ;
            GLfloat vertices[] =    {x, y,z,
                                    x+width, y, z,
                                    x+width, y+height, z,
                                    x, y+height, z};

            glBindBuffer(GL_ARRAY_BUFFER, verBuffer);
//            GLfloat vertex[] = { -0.5f, -0.5f, 0.0f,
//                                 0.5f, -0.5f, 0.0f,
//                                 0.5f, 0.5f, 0.0f,
//                                 -0.5f, 0.5f, 0.0f};

            // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) *12, formVertices(), GL_DYNAMIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        }
    }
    dirty->clearDirty();
}

Element::~Element() {
    //nothing
}

void Element::unload() {

}

