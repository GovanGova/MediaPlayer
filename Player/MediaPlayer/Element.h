//
// Created by G on 5/21/2018.
//

#pragma once

#include "Dirty.h"
#include <string>
#include "ScreenManager.h"
#include<vector>

// Base class for all asset
// Derive and add functionality
//

class Element
{
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

    void setSunAndMass(float x, float y, float z, float mass);
    void setVelocity(float x, float y, float z );
    virtual void tick(float t);
    virtual void render() = 0;
    virtual ~Element();
    virtual void unload();
    virtual void onWindowRestored();

  protected:
    virtual std::shared_ptr<std::vector<GLfloat>> formVertices(GLuint& vertexCount);
    glm::vec3 getGravity();
    GLuint m_verBuffer;
    shared_ptr<Dirty> m_dirty;
    string m_assetType = "";
    shared_ptr<screenManager> m_screenMng;
    GLfloat m_r{0}, m_g{1}, m_b{0}, m_a {1};
    //Image, video or another assets which needs time to load data
    bool m_isReady{false};
    
  private:
    float m_posX{0.0}, m_posY{0.0}, m_width{200.0}, m_height{200.0}, m_posZ{-10.0};
    glm::vec3 m_velocity{0.0,10.0,0};
    glm::vec3 m_pos; // final positong after gravity/velocity for each frame

    // Pulling particle mass and position
    //
    glm::vec3 m_pullingParticle{0.0,0.0,0.0};
    float m_pullingParticleMass{0.0};
    
    

    //int oID=

};