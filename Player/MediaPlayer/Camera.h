//
// Created by G on 5/16/2019.
//

#pragma once

#include "Base.h"

class Camera
{
public:
    Camera();
    void setEyePos(float x, float y, float z);
    
    void rotateCameraX(float angle); //in degree
    void rotateCameraY(float angle);
    void rotateCameraZ(float angle);

    glm::mat4 getViewMat();
    
    ~Camera();

private:
    glm::vec3 m_eyePos;
    glm::vec3 m_forward;
    glm::vec3 m_up;

    float m_xAngle{0.0}, m_yAngle{0.0}, m_zAngle{0.0};
};