//
// Created by G on 8/11/2018.
//

#ifndef SIGNAGE_PointSprite_H
#define SIGNAGE_PointSprite_H


#include "Texture.h"

// renders points
class PointSprite : public Texture
{

  protected:
    virtual std::shared_ptr<std::vector<GLfloat>> formVertices(GLuint &vertexCount);

  public:
    PointSprite(shared_ptr<screenManager> scm, int count);
    virtual void tick(float tSecs);
    virtual void render();
    virtual void unload();
    virtual void onWindowRestored();

    void setBreadth(uint32_t val)
    {
        this->breadth = val;
    }

    void setFilename(std::string filename)
    {
        this->m_filename = filename;
        m_bLoadTexture=true;
    }

    ~PointSprite();

    private:

    unsigned int m_count;
    uint32_t breadth = 10;
    float m_diffY = 0.0;
    glm::vec3 m_velocity{0,0,0};
    string m_filename;
    bool m_bLoadTexture = false;
    GLuint m_velocityBuffer{0};
    int m_stepCount{0};
};
#endif //SIGNAGE_PointSprite_H
