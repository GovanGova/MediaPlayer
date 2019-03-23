//
// Created by G on 5/29/2018.
//

#include "Shape.h"

Shape::Shape(shared_ptr<screenManager> screenMng)
    : Element(screenMng)
{
    m_assetType = "SHAPE";
}

void Shape::tick(float tSecs)
{

    Element::tick(tSecs);
}

void Shape::render()
{

    glUseProgram(m_screenMng->shapeProgram);
    glBindBuffer(GL_ARRAY_BUFFER, m_verBuffer);
    GLuint vertexLoc = glGetAttribLocation(m_screenMng->shapeProgram, "vVertex");
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    //glBindBuffer(GL_ARRAY_BUFFER,0);

    GLuint colorLoc = glGetUniformLocation(m_screenMng->shapeProgram, "vColor");
    glUniform4f(colorLoc, this->m_r, this->m_g, this->m_b, this->m_a);

    GLuint mvpLoc = glGetUniformLocation(m_screenMng->shapeProgram, "mvpMatrix");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(m_screenMng->getModelViewProjection()));

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableVertexAttribArray(vertexLoc);
        
    //  glEnable(GL_SCISSOR_TEST);
    //     glClearColor(0,0,0,1);
    //     glScissor(100,100,400, 400);
    //     glClear(GL_COLOR_BUFFER_BIT);   



    glUseProgram(0);
}

Shape::~Shape()
{
}