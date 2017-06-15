//
//  Windows.cpp
//  Game
//
//  Created by txh on 2017/5/24.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Windows.hpp"


Window::Window(int sampler,int width,int height,const char *title)
:drawFunc(nullptr)
{
    this->sampler = sampler;
    this->width = width;
    this->height = height;
    this->title = title;
    this->state = -1;
    this->window = NULL;
    this->enableDepthTest = false;
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

bool Window::setEnableDepthTest(bool flag)
{
    enableDepthTest = flag;
    if (flag) {
        glEnable(GL_DEPTH_TEST);
    }
    else
        glDisable(GL_DEPTH_TEST);
    return true;
}

bool Window::setEnableStencilTest(bool flag)
{
    enableStencilTest = flag;
    if (flag) {
        glEnable(GL_STENCIL_TEST);
    }
    else
        glDisable(GL_STENCIL_TEST);
    return true;
}


bool Window::setEnableResize(bool flag)
{
    if (flag) {
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    }
    else
    {
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }
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

bool Window::setMouseMoveCallback(mouseMoveCallback mmcb)
{
    if (mmcb == NULL) {
        return false;
    }
    glfwSetCursorPosCallback(window, mmcb);
    return true;
}

bool Window::setScollCallback(scrollCallback scb)
{
    if (scb == NULL) {
        return false;
    }
    glfwSetScrollCallback(window, scb);
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
        if (enableDepthTest) {
            glClear(GL_DEPTH_BUFFER_BIT);
        }
        if (enableStencilTest) {
            glClear(GL_STENCIL_BUFFER_BIT);
        }
        
        glfwPollEvents();
        
        
        if (drawFunc) {
            drawFunc();
        }
        
        
        glfwSwapBuffers(window);
    }
}
