#include "Camera.h"

Camera::Camera() : m_eyePos(0.0, 0.0, 100),
                   m_forward(0.0, 0.0, -1.0),
                   m_up(0.0, 1.0, 0.0)
{
}

void Camera::setEyePos(float x, float y, float z)
{
    m_eyePos = glm::vec3(x,y,z);
}

void Camera::rotateCameraX(float angle)
{
    m_xAngle = glm::radians(angle);
}

void Camera::rotateCameraY(float angle)
{
    m_yAngle = glm::radians(angle);
}

void Camera::rotateCameraZ(float angle)
{
    m_zAngle = glm::radians(angle);
}

glm::mat4 Camera::getViewMat()
{
    glm::mat4 viewMat= glm::lookAt(m_eyePos, m_forward, m_up);
    viewMat = glm::rotate(viewMat, m_xAngle, glm::vec3(1.0,0.0,0.0));
    viewMat = glm::rotate(viewMat, m_yAngle, glm::vec3(0.0,1.0,0.0));
    viewMat = glm::rotate(viewMat, m_zAngle, glm::vec3(0.0,0.0,1.0));

    return viewMat;
      
}
Camera::~Camera()
{
}