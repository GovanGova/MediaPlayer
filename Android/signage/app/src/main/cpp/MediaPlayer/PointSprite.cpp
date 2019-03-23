//#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "PointSprite.h"

PointSprite::PointSprite(shared_ptr<screenManager> scm, int count = 10) : Texture(scm),
                                                                          m_count(count),
                                                                          m_diffY(0.0f),
                                                                          m_velocity(0.0, 0.0, 0.0)
{
}

std::shared_ptr<std::vector<GLfloat>> PointSprite::formVertices(GLuint &count)
{
    std::vector<GLfloat> vertices;
     std::vector<GLfloat> velocity;
     std::uniform_real_distribution<float> distX(this->getPosX(), this->getPosX() + this->getWidth());
     std::uniform_real_distribution<float> distY(this->getPosY(), this->getPosY() + this->getHeight());
     std::uniform_real_distribution<float> distZ(this->getPosZ(), this->getPosZ() + this->breadth);
    
    
    for (uint32_t i = 0; i < m_count; i++)
    {
//        vertices.emplace_back(distX(range));
//        vertices.emplace_back(distY(range));
//        vertices.emplace_back(distZ(range));
        vertices.emplace_back(0);
        vertices.emplace_back(0);
        vertices.emplace_back(0);
    }

    std::uniform_real_distribution<float> velX(-1.0f, 1.0f);
    std::uniform_real_distribution<float> velY(-1.0f, 1.0f);
    std::uniform_real_distribution<float> velZ(-1.0f, 1.0f);
    for (uint32_t i = 0; i < m_count; i++)
    {
        velocity.emplace_back(velX(range));
        velocity.emplace_back(velY(range));
        velocity.emplace_back(velY(range));
    }
   glBindBuffer(GL_ARRAY_BUFFER, m_velocityBuffer);
   glBufferData(GL_ARRAY_BUFFER, this->m_count*3*sizeof(GLfloat), velocity.data(), GL_DYNAMIC_DRAW);
    
    count = this->m_count * 3;
    //std::cout<<"created_vertex\n";
    return make_shared<vector<GLfloat>>(vertices);
}

void PointSprite::tick(float tSecs)
{
    if (m_dirty->getDirtyFlag() == DF_ALL)
    {
       glGenBuffers(1, &m_velocityBuffer);        
    }

    Texture::tick(tSecs);
    if (m_bLoadTexture == true)
    {

        int w, h, bpp;
        unsigned char *data = stbi_load(m_filename.c_str(), &w, &h, &bpp, 0);
        loadTextureData(w, h, (const void *)data, bpp);

        free(data);

        m_bLoadTexture = false;
    }
    m_stepCount += 1;
}

void PointSprite::render()
{
    glUseProgram(m_screenMng->ptSpritePgm);

    glBindBuffer(GL_ARRAY_BUFFER, m_verBuffer);
    GLuint verLoc = glGetAttribLocation(m_screenMng->ptSpritePgm, "m_vVertex");
    glEnableVertexAttribArray(verLoc);
    glVertexAttribPointer(verLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);


    glBindBuffer(GL_ARRAY_BUFFER, m_velocityBuffer);
    GLuint velLoc = glGetAttribLocation(m_screenMng->ptSpritePgm, "m_vVelocity");
    glEnableVertexAttribArray(velLoc);
    glVertexAttribPointer(velLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glBindTexture(GL_TEXTURE_2D, m_textureID);    
    GLuint sampler = glGetUniformLocation(m_screenMng->ptSpritePgm, "sampler");
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(sampler, 0);

    GLuint stepCount = glGetUniformLocation(m_screenMng->ptSpritePgm, "stepCount");
    glUniform1i(stepCount, m_stepCount);

    GLuint colorLoc = glGetUniformLocation(m_screenMng->ptSpritePgm, "vColor");
    glUniform4f(colorLoc, this->m_r, this->m_g, this->m_b, this->m_a);

    GLuint pLoc = glGetUniformLocation(m_screenMng->ptSpritePgm, "m_projMat");
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(m_screenMng->getProjectionMatrix()));

    glm::mat4 mvMat = glm::mat4(1.0); // m_screenMng->getModelViewMatrix();
    //glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
    mvMat = m_screenMng->getModelViewMatrix();// * glm::translate(mvMat, m_velocity);
    GLuint mvLoc = glGetUniformLocation(m_screenMng->ptSpritePgm, "m_mvMat");
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
//    glEnable(GL_PROGRAM_POINT_SIZE);
  //  glEnable(GL_POINT_SPRITE);
    glDepthMask(false);
    
    glDrawArrays(GL_POINTS, 0, m_count);

    glDepthMask(true);
    glDisableVertexAttribArray(verLoc);
    //glDisable(GL_PROGRAM_POINT_SIZE);
    //glDisable(GL_POINT_SPRITE);
    glUseProgram(0);
}

void PointSprite::onWindowRestored()
{
    m_bLoadTexture = true;
    Element::onWindowRestored();
}
void PointSprite::unload()
{
    Texture::unload();
}

PointSprite::~PointSprite()
{
}