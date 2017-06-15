//
//  Windows.hpp
//  Game
//
//  Created by txh on 2017/5/24.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Windows_hpp
#define Windows_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>
#include <string>
using namespace std;
using namespace glm;


/**
 键盘回调函数

 @param GLFWwindow 窗口指针
 @param int 按键名
 @param int 按键特定动作
 @param int 按键状态
 @param int shift，control，alt是否被按下
 */
typedef void keyCallBack(GLFWwindow*,int,int,int,int);


/**
 鼠标回调函数

 @param GLFWwindow 窗口指针
 @param int 按键名
 @param int 按键状态
 @param int shift，control，alt是否被按下
 */
typedef void mouseCallBack(GLFWwindow*,int,int,int);


/**
 鼠标移动回调函数

 @param GLFWwindow 窗口指针
 @param int x轴偏移量
 @param int y轴偏移量
 */
typedef void mouseMoveCallback(GLFWwindow*,double,double);

/**
 鼠标滚轮回调函数

 @param GLFWwindow 窗口指针
 @param int x轴偏移量
 @param int y轴偏移量
 */
typedef void scrollCallback(GLFWwindow*,double,double);


typedef function<void()> DrawFunc;

class Window{
public:
    
    Window(int sampler,int width,int height,const char *title);
    ~Window();
    bool init();

    /**
     设置光标是否可见

     @param flag 光标是否可见
     @return true == 设置成功
     */
    bool setEnableCurse(bool flag);
    
    
    /**
     设置深度测试是否可用

     @param flag 是否启用
     @return true == 设置成功
     */
    bool setEnableDepthTest(bool flag);
    
    /**
     设置模版测试是否可用
     
     @param flag 是否启用
     @return true == 设置成功
     */
    bool setEnableStencilTest(bool flag);
    
    
    /**
     设置窗口可伸缩性

     @param flag 是否启用
     @return true == 设置成功
     */
    bool setEnableResize(bool flag);
    
    /**
     设置键盘回调函数

     @param kcb 键盘回调函数
     @return true == 设置成功
     */
    bool setKeyCallback(keyCallBack kcb);
    
    
    /**
     设置鼠标回调函数

     @param mcb 鼠标回调函数
     @return true == 设置成功
     */
    bool setMouseCallback(mouseCallBack mcb);
    
    /**
     设置鼠标移动回调函数

     @param mmcb 鼠标移动回调函数
     @return true == 设置成功
     */
    bool setMouseMoveCallback(mouseMoveCallback mmcb);
    
    /**
     设置滚轮回调函数

     @param scb 滚轮回调函数
     @return true == 设置成功
     */
    bool setScollCallback(scrollCallback scb);
    
    
    /**
     设置窗口背景颜色

     @param backColor rgb背景颜色
     @return true == 设置成功
     */
    bool setBackgroundColor(vec3 backColor);
    
    
    /**
     设置用于窗口内绘制的回调函数

     @param df 绘制回调函数
     @return true == 设置成功
     */
    bool draw(DrawFunc df);
    
    
    /**
     显示函数，并处理响应事件
     */
    void loop();
private:
    
    //抗锯齿数
    GLint sampler;
    //窗口宽度
    GLint width;
    //窗口高度
    GLint height;
    //窗口名称
    string title;
    GLint state;
    GLFWwindow *window;
    DrawFunc drawFunc;
    bool enableDepthTest;
    bool enableStencilTest;
};

#endif /* Windows_hpp */
