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

extern float skyboxVertices[];
extern GLfloat cubeVertices[];

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
    glViewport(0, 0, WIDTH*2, HEIGHT*2);
    
    camera.reset(new Camera(cameraPos));
    
    
    shared_ptr<Shader> skyboxShader = ResourceManeger::loadShader("Script/skybox.vertex", "Script/skybox.fragment", "skybox");
    shared_ptr<Shader> cubeShader = ResourceManeger::loadShader("Script/cube.vertex", "Script/cube.fragment", "cube");
    shared_ptr<Texture> cubeTexture = ResourceManeger::loadTexture("textures/container2.png", "cube");
    
    VertexArray cubeVao;
    cubeVao.setBuffer(cubeVertices, 180 * sizeof(GLfloat));
    cubeVao.setBufferAttrib(0, 3, 6 * sizeof(GLfloat), (GLvoid*)0);
    cubeVao.setBufferAttrib(1, 3, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
                            
    
    VertexArray skybox;
    skybox.setBuffer(skyboxVertices,108 * sizeof(float));
    skybox.setBufferAttrib(0,3, 3* sizeof(GLfloat), (GLvoid*)0);
    
    vector<const GLchar*> faces;
    faces.push_back("/Users/zj-db0860/LearnOpenGL/6.cubeMaps/textures/skybox/right.jpg");
    faces.push_back("/Users/zj-db0860/LearnOpenGL/6.cubeMaps/textures/skybox/left.jpg");
    faces.push_back("/Users/zj-db0860/LearnOpenGL/6.cubeMaps/textures/skybox/top.jpg");
    faces.push_back("/Users/zj-db0860/LearnOpenGL/6.cubeMaps/textures/skybox/bottom.jpg");
    faces.push_back("/Users/zj-db0860/LearnOpenGL/6.cubeMaps/textures/skybox/back.jpg");
    faces.push_back("/Users/zj-db0860/LearnOpenGL/6.cubeMaps/textures/skybox/front.jpg");
    GLuint cubemapTexture = loadCubemap(faces);
    
    win.draw([&](){
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        Do_Movement();
        
 
        mat4 projection = glm::perspective(glm::radians(camera->getZoom()), (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1f, 100.0f);
        mat4 view = camera->getViewMatrix();
        mat4 model;
        
        glDepthFunc(GL_LEQUAL);
        
        cubeShader->use();
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        view = camera->getViewMatrix();
        cubeShader->setUniformMatrix4fv("model", model);
        cubeShader->setUniformMatrix4fv("view", view);
        cubeShader->setUniformMatrix4fv("projection", projection);
        cubeShader->setUniformVector3f("cameraPos", camera->getPosition());
        
        // Cubes
        cubeVao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        
        
        skyboxShader->use();
        view = glm::mat4(glm::mat3(camera->getViewMatrix()));
        skyboxShader->setUniformMatrix4fv("model", model);
        skyboxShader->setUniformMatrix4fv("view", view);
        skyboxShader->setUniformMatrix4fv("projection", projection);
        skybox.bind();
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        skybox.unbind();
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
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

GLfloat skyboxVertices[] = {
    // Positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

GLfloat cubeVertices[] = {
    // Positions          // Normals
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
