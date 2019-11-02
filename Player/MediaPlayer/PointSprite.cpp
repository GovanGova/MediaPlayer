//#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "PointSprite.h"

PointSprite::PointSprite(shared_ptr<screenManager> scm, int count) : Texture(scm),
                                                                     m_count(count)
{
}

void PointSprite::setBreadth(uint32_t val)
{
    this->m_breadth = val;
}

void PointSprite::setFilename(std::string filename)
{
    this->m_filename = filename;
    m_bLoadTexture = true;
}

void PointSprite::setVelocityRanges(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
    m_xMin = xMin;
    m_xMax = xMax;
    m_yMin = yMin;
    m_yMax = yMax;
    m_zMin = zMin;
    m_zMax = zMax;
}

void PointSprite::setAcceleration(float x, float y, float z)
{
   m_accelerate = glm::vec3(x, y, z);
}

std::shared_ptr<std::vector<GLfloat>> PointSprite::formVertices(GLuint &count)
{
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> velocity;

    std::uniform_real_distribution<float> distX(getPosX()- getWidth(), getPosX()+ getWidth());
    std::uniform_real_distribution<float> distY(getPosY() - getHeight(), getPosY() + getHeight());
    std::uniform_real_distribution<float> distZ(getPosZ()- m_breadth,  getPosZ() + m_breadth);

    std::uniform_real_distribution<float> velX(m_xMin, m_xMax);
    std::uniform_real_distribution<float> velY(m_yMin, m_yMax);
    std::uniform_real_distribution<float> velZ(m_zMin, m_zMax);

    for (uint32_t i = 0; i < m_count; i++)
    {
        vertices.emplace_back(distX(range));
        vertices.emplace_back(distY(range));
        vertices.emplace_back(distZ(range));

        velocity.emplace_back(velX(range));
        velocity.emplace_back(velY(range));
        velocity.emplace_back(velZ(range));
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
        if (!glIsBuffer(m_velocityBuffer))
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
    mvMat = m_screenMng->getModelViewMatrix() * glm::translate(mvMat, m_accelerate*float(m_stepCount));
    GLuint mvLoc = glGetUniformLocation(m_screenMng->ptSpritePgm, "m_mvMat");
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SPRITE);
    glDepthMask(false);
    
    glDrawArrays(GL_POINTS, 0, m_count);

    glDepthMask(true);
    glDisableVertexAttribArray(verLoc);
    glDisable(GL_PROGRAM_POINT_SIZE);
    glDisable(GL_POINT_SPRITE);
    glUseProgram(0);
}

void PointSprite::onWindowRestored()
{
    m_bLoadTexture = true;
    Element::onWindowRestored();
}
void PointSprite::unload()
{
    glDeleteBuffers(1, &m_velocityBuffer);
    Texture::unload();
}

PointSprite::~PointSprite()
{
}