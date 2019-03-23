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
    m_posX = m_posY = 0;
    m_width = m_height = 200;
    m_posZ = -10.0;
    m_isReady = false;
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

void Element::tick(float tSecs)
{
    // Create vertex buffer
    //
    if (m_dirty->getDirtyFlag() == DF_ALL)
    {
        glGenBuffers(1, &m_verBuffer);
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
