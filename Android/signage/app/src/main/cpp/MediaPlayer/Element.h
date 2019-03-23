//
// Created by G on 5/21/2018.
//

#ifndef SIGNAGE_ELEMENT_H
#define SIGNAGE_ELEMENT_H

#include "Dirty.h"
#include <string>
#include "ScreenManager.h"
#include<vector>

// Base class for all asset
// Derive and add functionality
//

class Element
{
  private:
    float m_posX, m_posY, m_width, m_height, m_posZ;

    //Image, video or another assets which needs time to load data
    bool m_isReady;

    //int oID=

  protected:
    virtual std::shared_ptr<std::vector<GLfloat>> formVertices(GLuint& vertexCount);
    GLuint m_verBuffer;
    shared_ptr<Dirty> m_dirty;
    string m_assetType = "";
    shared_ptr<screenManager> m_screenMng;
    GLfloat m_r{0}, m_g{1}, m_b{0}, m_a {1};

  public:
    Element(shared_ptr<screenManager> screenMng);

    void setPosX(float posX);
    void setPosY(float posY);
    void setPosZ(float posZ);

    float getPosX() { return m_posX; }
    float getPosY() { return m_posY; }
    float getPosZ() { return m_posZ; }

    void setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
    string getAssetType() { return m_assetType; }
    void setHeight(float h);
    float getHeight() { return m_height; }

    void setWidth(float w);
    float getWidth() { return m_width; }

    void setAlpha(GLfloat a);
    float getAlpha() { return m_a; }

    virtual void tick(float t);
    virtual void render() = 0;
    virtual ~Element();
    virtual void unload();
    virtual void onWindowRestored();
};

#endif //SIGNAGE_ELEMENT_H
