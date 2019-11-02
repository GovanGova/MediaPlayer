//
// Created by G on 5/21/2018.
//

#include "Element.h"

// Element class member function
//
Element::Element(shared_ptr<screenManager> screenMng)
    : m_screenMng(screenMng),
      m_dirty(shared_ptr<Dirty>(new Dirty()))

{
}

void Element::setPosX(float x)
{
    if (m_posX != x)
    {
        m_posX = x;
        m_dirty->setDirty(DF_XY);
    }
}

void Element::setPosY(float y)
{
    if (m_posY != y)
    {
        m_posY = y;
        m_dirty->setDirty(DF_XY);
    }
}

void Element::setPosZ(float z)
{
    if (m_posZ != z)
    {
        m_posZ = z;
        m_dirty->setDirty(DF_XY);
    }
}
void Element::setHeight(float h)
{
    if (m_height != h)
    {
        m_height = h;
        m_dirty->setDirty(DF_WH);
    }
}

void Element::setWidth(float w)
{
    if (m_width != w)
    {
        m_width = w;
        m_dirty->setDirty(DF_WH);
    }
}

void Element::setAlpha(GLfloat a)
{
    m_a = a;
}

void Element::setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A)
{
    this->m_r = R;
    this->m_g = G;
    this->m_b = B;
    this->m_a = A;
}

std::shared_ptr<std::vector<GLfloat>> Element::formVertices(GLuint &vertexCount)
{
    GLfloat x = m_posX, y = m_posY, z = m_posZ;
    GLuint count = 12;

    //            GLfloat vertex[] = { -0.5f, -0.5f, 0.0f,
    //                                 0.5f, -0.5f, 0.0f,
    //                                 0.5f, 0.5f, 0.0f,
    //                                 -0.5f, 0.5f, 0.0f};
    std::vector<GLfloat> vert{x, y + m_height, z,
                              x, y, z,
                              x + m_width, y, z,
                              x + m_width, y + m_height, z};
    auto vertices = std::make_shared<std::vector<GLfloat>>(vert);
    vertexCount = count;
    return vertices;
}

void Element::onWindowRestored()
{
    m_dirty->setDirty(DF_ALL);
}

void Element::setSunAndMass(float x, float y, float z, float mass)
{
    m_pullingParticle = glm::vec3(x, y, z);
    m_pullingParticleMass = mass;
}

void Element::setVelocity(float x, float y, float z)
{
    m_velocity.x = x;
    m_velocity.y = y;
    m_velocity.z = z;
}
glm::vec3 Element::getGravity()
{
    if (m_pullingParticleMass != 0)
    {

        auto vector = m_pullingParticle - m_pos;
        auto length = glm::length(vector);
        // rule gravity = mass of particle / square of distance between two particle 
        //
        auto gravityLength = m_pullingParticleMass / (length * length);
        
        m_velocity += vector * (gravityLength / length);
        m_pos = m_pos + m_velocity;
    }
    return glm::vec3(m_pos.x - m_posX, m_pos.y - m_posY, m_pos.z - m_posZ);
}

void Element::tick(float tSecs)
{
    // Create vertex buffer
    //
    if (m_dirty->getDirtyFlag() == DF_ALL)
    {
        if (!glIsBuffer(m_verBuffer))
            glGenBuffers(1, &m_verBuffer);
        //Initally
        //
        m_pos = glm::vec3(m_posX, m_posY, m_posZ);
    }
    if (m_dirty->getDirtyFlag() != DF_NONE)
    {
        if (m_dirty->getDirtyFlag() & DF_XY || m_dirty->getDirtyFlag() & DF_WH)
        {

            GLuint vertexCount = 0;
            auto vertices = formVertices(vertexCount);
            glBindBuffer(GL_ARRAY_BUFFER, m_verBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexCount, vertices->data(), GL_DYNAMIC_DRAW);
            //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        }
    }
    m_dirty->clearDirty();
}

Element::~Element()
{
    unload();
}

void Element::unload()
{
    glDeleteBuffers(1, &m_verBuffer);
}
