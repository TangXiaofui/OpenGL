//
//  Windows.cpp
//  Game
//
//  Created by txh on 2017/5/24.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Windows.hpp"


Window::Window(int sampler,int width,int height,const char *title)
{
    this->sampler = sampler;
    this->width = width;
    this->height = height;
    this->title = title;
    this->state = -1;
    this->window = NULL;
}
Window::~Window()
{
    if (state == 0) {
        glfwTerminate();
    }
}
bool Window::init()
{
    if (!glfwInit()) {
        return false;
    }
    else
        state = 0;
    //设置抗锯齿
    glfwWindowHint(GLFW_SAMPLES, 4);
    //设置主次版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //前向兼容
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    //启动核心版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //若title为空，则设置默认值
    if (title.size() == 0) {
        this->title == "window";
    }
    
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL) {
        return false;
    }
    
    glfwMakeContextCurrent(window);
    return true;
}

bool Window::setEnableCurse(bool flag)
{
    if (flag) {
        glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_NORMAL);
    }
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return true;
}

bool Window::setKeyCallback(keyCallBack kcb)
{
    if (kcb == NULL) {
        return false;
    }
    glfwSetKeyCallback(window, kcb);
    return true;
}
bool Window::setMouseCallback(mouseCallBack mcb)
{
    if (mcb == NULL) {
        return false;
    }
    glfwSetMouseButtonCallback(window, mcb);
    return true;
}

bool Window::setBackgroundColor(vec3 backColor)
{
    glClearColor(backColor.r,backColor.g,backColor.b,1.0f);
    return true;
}
bool Window::draw(DrawFunc df)
{
    if (df == NULL) {
        return false;
    }
    drawFunc = df;
    return true;
}
void Window::loop()
{
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        
        drawFunc();
        
        
        glfwSwapBuffers(window);
    }
}
