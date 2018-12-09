//
// Created by G on 5/29/2018.
//

#include "Shape.h"

Shape::Shape(shared_ptr<screenManager> screenMng)
    : Element(screenMng)
{
    assetType="SHAPE";
}

void Shape::tick(float tSecs){

    Element::tick(tSecs);
}

void Shape::render(){

    glUseProgram(screenMng->shapeProgram);

    glBindBuffer(GL_ARRAY_BUFFER, verBuffer);
    GLuint vertexLoc = glGetAttribLocation(screenMng->shapeProgram,"vVertex");
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc,3,GL_FLOAT,GL_FALSE,0,NULL);
    //glBindBuffer(GL_ARRAY_BUFFER,0);

    GLuint colorLoc = glGetUniformLocation(screenMng->shapeProgram,"vColor");
    glUniform4f(colorLoc, 1,0,0,1);

    GLuint mvpLoc = glGetUniformLocation(screenMng->shapeProgram,"mvpMatrix");
    glUniformMatrix4fv(mvpLoc,1,GL_FALSE, glm::value_ptr(screenMng->getModelViewProjection()));

    glDrawArrays(GL_TRIANGLE_FAN,0,4);
    glDisableVertexAttribArray(vertexLoc);

    //glUseProgram(0);
}


Shape::~Shape(){

}