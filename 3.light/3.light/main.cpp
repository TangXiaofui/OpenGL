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

extern GLfloat vertices[];
extern glm::vec3 cubePositions[];
extern glm::vec3 pointLightPositions[];

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


int main(int argc, const char * argv[]) {
    
    Window win(4,WIDTH,HEIGHT,"light");
    win.init();
    win.setBackgroundColor(vec3(0.0f));
    win.setKeyCallback(key_callback);
    win.setMouseMoveCallback(mouse_callback);
    win.setScollCallback(scroll_callback);
    win.setEnableDepthTest(true);
    win.setBackgroundColor(vec3(0.1f,0.1f,0.1f));
    
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        return -1;
    }
    glViewport(0, 0, WIDTH*2, HEIGHT*2);
    
    camera.reset(new Camera(cameraPos));
    
    shared_ptr<Shader> cubeShader = ResourceManeger::loadShader("Script/cood.vertex", "Script/cood.fragment", "cube");
    shared_ptr<Shader> lightShader = ResourceManeger::loadShader("Script/light.vertex", "Script/light.fragment", "light");
    shared_ptr<Texture> cubeTexture = ResourceManeger::loadTexture("textures/container2.png", "cube");
    shared_ptr<Texture> cubeSpecularTexture = ResourceManeger::loadTexture("textures/container2_specular.png", "cubeSpecular");
    
    VertexArray cubeVao;
    cubeVao.setBuffer(vertices, 288 * sizeof(GLfloat));
    cubeVao.setBufferAttrib(0, 3, 8 * sizeof(GLfloat), (GLvoid*)0);
    cubeVao.setBufferAttrib(1, 3, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    cubeVao.setBufferAttrib(2, 2, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    
    VertexArray lightVao;
    lightVao.setBuffer(vertices, 288 * sizeof(GLfloat));
    lightVao.setBufferAttrib(0, 3, 8 * sizeof(GLfloat), (GLvoid*)0);
    
    win.draw([&](){
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        Do_Movement();
        
        cubeShader->use();
        
        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
        lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
        

        cubeShader->setUniformVector3f("viewPos", cameraPos);
        
        //物体材质属性
        cubeShader->setUniform1f("material.diffuse", 0.0f);
        cubeShader->setUniform1f("material.specular", 1.0f);
        cubeShader->setUniform1f("material.shininess", 32.0f);
        
        //平行光
        cubeShader->setUniformVector3f("dirLight.direction",vec3(-0.2f, -1.0f, -0.3f));
        cubeShader->setUniformVector3f("dirLight.ambient", vec3(0.05f));
        cubeShader->setUniformVector3f("dirLight.diffuse", vec3(0.4f));
        cubeShader->setUniformVector3f("dirLight.specular", vec3(0.5f));
  
        
        //点光源
        for (int i = 0 ; i < 4; ++i) {
            char buf[1024] = {0};
            snprintf(buf, 1024, "pointLights[%d].position",i);
            cubeShader->setUniformVector3f(buf, pointLightPositions[i]);
            
            snprintf(buf, 1024, "pointLights[%d].ambient",i);
            cubeShader->setUniformVector3f(buf, vec3(0.05f));
            
            snprintf(buf, 1024, "pointLights[%d].diffuse",i);
            cubeShader->setUniformVector3f(buf, vec3(0.8));
            
            snprintf(buf, 1024, "pointLights[%d].specular",i);
            cubeShader->setUniformVector3f(buf, vec3(1.0f));
            
            snprintf(buf, 1024, "pointLights[%d].constant",i);
            cubeShader->setUniform1f(buf,1.0f);
            
            snprintf(buf, 1024, "pointLights[%d].linear",i);
            cubeShader->setUniform1f(buf, 0.09);
            
            snprintf(buf, 1024, "pointLights[%d].quadratic",i);
            cubeShader->setUniform1f(buf, 0.032);
            
        }
        
        //手电筒
        cubeShader->setUniformVector3f("spotLight.position", camera->getPosition());
        cubeShader->setUniformVector3f("spotLight.direction", camera->getFront());
        cubeShader->setUniformVector3f("spotLight.ambient", vec3(0.0f));
        cubeShader->setUniformVector3f("spotLight.diffuse", vec3(1.0f));
        cubeShader->setUniformVector3f("spotLight.specular", vec3(1.0f));
        cubeShader->setUniform1f("spotLight.constant", 1.0f);
        cubeShader->setUniform1f("spotLight.linear", 0.09f);
        cubeShader->setUniform1f("spotLight.quadratic", 0.032f);
        cubeShader->setUniform1f("spotLight.cutOff",  glm::cos(glm::radians(12.5f)));
        cubeShader->setUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        
        
        mat4 model;
        mat4 view = camera->getViewMatrix();
        mat4 projection = perspective(camera->getZoom(), GLfloat(WIDTH)/GLfloat(HEIGHT), 0.1f, 100.0f);
        
        cubeShader->setUniformMatrix4fv("model", model);
        cubeShader->setUniformMatrix4fv("view", view);
        cubeShader->setUniformMatrix4fv("projection", projection);
        
        cubeTexture->use();
        cubeSpecularTexture->use(1);
        
        for(GLuint i = 0; i < 10; i++)
        {
            model = glm::mat4();
            model = glm::translate(model, cubePositions[i]);
            GLfloat angle = 20.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            cubeShader->setUniformMatrix4fv("model", model);
            cubeVao.bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
            cubeVao.unbind();
        }
        
        
        lightShader->use();
        
        model = mat4();
        model = glm::translate(model, lightPos);
        model = glm::scale(model, vec3(0.2f));
        
        lightShader->setUniformMatrix4fv("model", model);
        lightShader->setUniformMatrix4fv("view", view);
        lightShader->setUniformMatrix4fv("projection", projection);
        
        for (GLuint i = 0; i < 4; i++)
        {
            model = glm::mat4();
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            lightShader->setUniformMatrix4fv("model", model);
            
            
            lightVao.bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
            lightVao.unbind();
        }
        
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
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};
