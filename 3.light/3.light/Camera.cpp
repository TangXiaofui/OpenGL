//
//  Camera.cpp
//  3.light
//
//  Created by txh on 2017/6/5.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Camera.hpp"


Camera::Camera(vec3 pos, vec3 up, GLfloat yaw, GLfloat pitch)
:front(vec3(0.0f,0.0f,-1.0f))
{
    this->position = pos;
    this->worldup = up;
    this->yaw = yaw;
    this->pitch = pitch;
    this->mouseMoveSpeed = SPEED;
    this->mouseSensitivity = SENSITIVITY;
    this->zoom = ZOOM;
    this->updateCameraVector();
}

mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(CameraMovement direction, GLfloat deltaTime)
{
    GLfloat velocity = this->mouseMoveSpeed * deltaTime;
    if (direction == FORWARD) {
        this->position += this->front * velocity;
    }
    else if(direction == BACKWARD){
        this->position -= this->front * velocity;
    }
    else if(direction == LEFT){
        this->position -= this->right * velocity;
    }
    else if(direction == RIGHT){
        this->position += this->right * velocity;
    }
}

void Camera::processMouseMovement(GLfloat xoffset,GLfloat yoffset,GLboolean constractPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;
    
    yaw += xoffset;
    pitch += yoffset;
    
    if (constractPitch) {
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }
    this->updateCameraVector();
}

void Camera::processMouseScroll(GLfloat yoffset)
{
    if (this->zoom >= 1.0f && this->zoom <= 45.0f) {
        this->zoom -= yoffset;
    }
    if (this->zoom < 1.0f) {
        this->zoom = 1.0f;
    }
    if (this->zoom > 45.0f) {
        this->zoom = 45.0f;
    }
}

void Camera::updateCameraVector()
{
    vec3 tmp;
    tmp.x = cos(radians(pitch)) * cos(radians(yaw));
    tmp.y = sin(radians(pitch));
    tmp.z = cos(radians(pitch)) *sin(radians(yaw));
    this->front = normalize(tmp);
    this->right = normalize(cross(this->front, this->worldup));
    this->up = normalize(cross(this->right, this->front));
    
}

GLfloat Camera::getZoom()
{
    return zoom;
}

vec3 Camera::getPosition()
{
    return position;
}
vec3 Camera::getFront()
{
    return front;
}
