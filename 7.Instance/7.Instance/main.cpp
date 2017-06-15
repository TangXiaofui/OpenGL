//
//  main.cpp
//  3.light
//
//  Created by txh on 2017/6/5.
//  Copyright © 2017年 txh. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "Windows.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "ResourceManager.hpp"
#include "VertexArray.hpp"
#include "Camera.hpp"

using namespace std;
using namespace glm;

#define WIDTH  800
#define HEIGHT 600


unique_ptr<Camera> camera;
bool keys[1024] = {false};
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

bool isFirstMouse = true;
GLfloat lastX = WIDTH/2;
GLfloat lastY = HEIGHT/2;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 cameraPos(0.0f, 0.0f,5.0f);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();
GLuint loadCubemap(vector<const GLchar*> faces);

GLfloat quadVertices[] = {
    //  ---位置---   ------颜色-------
    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
    0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
    -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
    
    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
    0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
    0.05f,  0.05f,  0.0f, 1.0f, 1.0f
};
int main(int argc, const char * argv[]) {
    
    Window win(4,WIDTH,HEIGHT,"light");
    win.init();
    win.setBackgroundColor(vec3(0.0f));
    win.setKeyCallback(key_callback);
    win.setMouseMoveCallback(mouse_callback);
    win.setScollCallback(scroll_callback);
    win.setEnableDepthTest(true);
    win.setBackgroundColor(vec3(0.3f));

    
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        return -1;
    }
    glViewport(0, 0, WIDTH * 2, HEIGHT * 2);
    
    camera.reset(new Camera(cameraPos));
    
    //1.
//    shared_ptr<Shader> thingShader = ResourceManeger::loadShader("Script/thing.vertex", "Script/thing.fragment", "thing");
    //2.
    shared_ptr<Shader> thingShader = ResourceManeger::loadShader("Script/InstanceArray.vertex", "Script/InstanceArray.fragment", "InstanceArray");
    VertexArray thingVao;
    thingVao.setBuffer(quadVertices, sizeof(quadVertices));
    thingVao.setBufferAttrib(0, 2, 5 * sizeof(GLfloat), (GLvoid*)0);
    thingVao.setBufferAttrib(1, 3, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glm::vec2 translations[100];
    int index = 0;
    GLfloat offset = 0.1f;
    for(GLint y = -10; y < 10; y += 2)
    {
        for(GLint x = -10; x < 10; x += 2)
        {
            glm::vec2 translation;
            translation.x = (GLfloat)x / 10.0f + offset;
            translation.y = (GLfloat)y / 10.0f + offset;
            translations[index++] = translation;
        }
    }
    //2.
    thingVao.bind();
    unsigned int instanceVBO;
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);
    thingVao.unbind();
    
    
    win.draw([&](){
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        Do_Movement();
        
        thingShader->use();
        //1.
//        for(GLuint i = 0; i < 100; i++)
//        {
//            stringstream ss;
//            string index;
//            ss << i;
//            index = ss.str();
//            thingShader->setUniformVector2f(("offsets[" + index + "]").c_str(), translations[i]);
//        }
// 
//        thingVao.bind();
//        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
        //2.
        thingVao.bind();
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
        thingVao.unbind();
    });
    
    
    
    win.loop();
    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if(key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS) {
            keys[key] = true;
        }
        else if(action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->processMouseScroll(yoffset);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (isFirstMouse) {
        lastX = xpos;
        lastY = ypos;
        isFirstMouse = false;
    }
    
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    
    lastX = xpos;
    lastY = ypos;
    
    camera->processMouseMovement(xoffset, yoffset);
}

void Do_Movement()
{
    if(keys[GLFW_KEY_W]){
        camera->processKeyboard(FORWARD, deltaTime);
    }
    if (keys[GLFW_KEY_S]) {
        camera->processKeyboard(BACKWARD, deltaTime);
    }
    if (keys[GLFW_KEY_A]) {
        camera->processKeyboard(LEFT, deltaTime);
    }
    if (keys[GLFW_KEY_D]) {
        camera->processKeyboard(RIGHT, deltaTime);
    }
}

GLuint loadCubemap(vector<const GLchar*> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    
    int width,height;
    unsigned char* image;
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < faces.size(); i++)
    {
        image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(
                     GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                     GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
                     );
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    return textureID;
}

