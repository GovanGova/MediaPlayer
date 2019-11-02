//
// Created by G on 8/11/2018.
//

#pragma once


#include "Texture.h"

// renders points
class PointSprite : public Texture
{

  protected:
    virtual std::shared_ptr<std::vector<GLfloat>> formVertices(GLuint &vertexCount);

  public:
    PointSprite(shared_ptr<screenManager> scm, int count = 10);
    void tick(float tSecs) override;
    void render() override;
    void unload() override;
    void onWindowRestored() override;

    void setAcceleration(float xComp, float yComp, float zComp);
    void setFilename(std::string filename);
    void setBreadth(uint32_t val);
    void setVelocityRanges(float xMin=0, float xMax =0, float yMin =0, float yMax = 0, float zMin=0, float zMax=0);
    

    ~PointSprite();

  private:

    unsigned int m_count;
    uint32_t m_breadth = 10;
    float m_diffY = 0.0;
    glm::vec3 m_accelerate{0,0,0};
    string m_filename;
    bool m_bLoadTexture = false;
    GLuint m_velocityBuffer{0};
    int m_stepCount{0};
    float m_xMin{0.0}, m_xMax{0.0};
    float m_yMin{0.0}, m_yMax{0.0};
    float m_zMin{0.0}, m_zMax{0.0};
};
