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

extern float vertices[];
extern GLfloat planeVertices[];

int main(int argc, const char * argv[]) {
    
    Window win(4,WIDTH,HEIGHT,"light");
    win.init();
    win.setBackgroundColor(vec3(0.0f));
    win.setKeyCallback(key_callback);
    win.setMouseMoveCallback(mouse_callback);
    win.setScollCallback(scroll_callback);
    win.setEnableDepthTest(true);
    win.setBackgroundColor(vec3(0.3f));
    win.setEnableStencilTest(true);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        return -1;
    }
    glViewport(0, 0, WIDTH*2, HEIGHT*2);
    
    camera.reset(new Camera(cameraPos));
    
    shared_ptr<Shader> AdvanceShader = ResourceManeger::loadShader("Script/Advanced.vertex", "Script/Advanced.fragment", "Advance");
    shared_ptr<Shader> singleColorShader = ResourceManeger::loadShader("Script/Advanced.vertex", "Script/SingleColor.fragment", "SingleColor");
    
    VertexArray cubeVao,planeVao;
    cubeVao.setBuffer(vertices,180 * sizeof(float));
    cubeVao.setBufferAttrib(0, 3, 5 * sizeof(float), (GLvoid*)0);
    cubeVao.setBufferAttrib(1, 2, 5 * sizeof(float), (GLvoid*)(3 * sizeof(GLfloat)));
    
    planeVao.setBuffer(planeVertices ,30 * sizeof(float));
    planeVao.setBufferAttrib(0, 3, 5 * sizeof(float), (GLvoid*)0);
    planeVao.setBufferAttrib(1, 2, 5 * sizeof(float), (GLvoid*)(3 * sizeof(GLfloat)));
    
    shared_ptr<Texture> cubeTexture = ResourceManeger::loadTexture("textures/marble.jpg", "cube");
    shared_ptr<Texture> planeTexture = ResourceManeger::loadTexture("textures/metal.png", "plane");
    
    win.draw([&](){
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        
        Do_Movement();
        
 
        mat4 projection = glm::perspective(glm::radians(camera->getZoom()), (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1f, 100.0f);
        mat4 view = camera->getViewMatrix();
        mat4 model;
        
        singleColorShader->use();
        singleColorShader->setUniformMatrix4fv("view", view);
        singleColorShader->setUniformMatrix4fv("projection", projection);
        
        AdvanceShader->use();
        AdvanceShader->setUniformMatrix4fv("view", view);
        AdvanceShader->setUniformMatrix4fv("projection", projection);
        
        
        glStencilMask(0x00);
        planeVao.bind();
        planeTexture->use();
        model = glm::mat4();
        AdvanceShader->setUniformMatrix4fv("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        planeVao.unbind();
        
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        cubeVao.bind();
        cubeTexture->use();
        
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        AdvanceShader->setUniformMatrix4fv("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
       
        model = mat4();
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        AdvanceShader->setUniformMatrix4fv("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        cubeVao.unbind();
        
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        singleColorShader->use();
        GLfloat scale = 1.05;
        
        cubeVao.bind();
        cubeTexture->use();
        
        model = mat4();
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        singleColorShader->setUniformMatrix4fv("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        model = mat4();
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        singleColorShader->setUniformMatrix4fv("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glStencilMask(0xFF);
        glEnable(GL_DEPTH_TEST);
        
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


float vertices[] = {
    // Positions          // Texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
GLfloat planeVertices[] = {
    // Positions            // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
    5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    
    5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    5.0f,  -0.5f, -5.0f,  2.0f, 2.0f
};
