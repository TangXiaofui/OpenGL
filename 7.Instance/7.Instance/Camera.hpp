//
//  Camera.hpp
//  3.light
//
//  Created by txh on 2017/6/5.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;


enum CameraMovement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;


class Camera{
public:
    Camera(vec3 pos = vec3(0.0f,0.0f,0.0f), vec3 up = vec3(0.0f,1.0f,0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
    mat4 getViewMatrix();
    void processKeyboard(CameraMovement direction, GLfloat deltaTime);
    void processMouseMovement(GLfloat xoffset,GLfloat yoffset,GLboolean constractPitch = true);
    void processMouseScroll(GLfloat yoffset);
    void updateCameraVector();
    GLfloat getZoom();
    vec3 getPosition();
    vec3 getFront();

private:
    vec3 position;
    vec3 worldup;
    vec3 up;
    vec3 front;
    vec3 right;
    
    GLfloat yaw;
    GLfloat pitch;
    GLfloat zoom;
    GLfloat mouseMoveSpeed;
    GLfloat mouseSensitivity;
    
};


#endif /* Camera_hpp */
