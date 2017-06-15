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
#include "ResourceManager.hpp"
#include "VertexArray.hpp"
#include "Camera.hpp"
#include "Model.hpp"

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


//mesh和model内部存在bug，临时对象析gou，导致刚加载的纹理即删除

int main(int argc, const char * argv[]) {
    
    Window win(4,WIDTH,HEIGHT,"light");
    win.init();
    win.setBackgroundColor(vec3(0.0f));
    win.setKeyCallback(key_callback);
    win.setMouseMoveCallback(mouse_callback);
    win.setScollCallback(scroll_callback);
    win.setEnableDepthTest(true);
    win.setBackgroundColor(vec3(0.5f));
    
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        return -1;
    }
    glViewport(0, 0, WIDTH*2, HEIGHT*2);
    
    camera.reset(new Camera(cameraPos));
    shared_ptr<Shader> modelShader = ResourceManeger::loadShader("Script/Model.vertex", "Script/Model.fragment", "model");
    Model ourModel("/Users/zj-db0860/Note/4.Assimp/Model/nanosuit.obj");
    
    
    win.draw([&](){
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        Do_Movement();
        
        modelShader->use();
        
        glm::mat4 projection = glm::perspective(glm::radians(camera->getZoom()), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = camera->getViewMatrix();
        modelShader->setUniformMatrix4fv("projection", projection);
        modelShader->setUniformMatrix4fv("view", view);
        
        // render the loaded model
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        modelShader->setUniformMatrix4fv("model", model);
        ourModel.Draw(modelShader);
        

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


