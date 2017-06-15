//
//  Button.hpp
//  Game
//
//  Created by txh on 2017/5/26.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include <iostream>
#include "Utility.hpp"
#include "Object.hpp"
#include "VertexArray.hpp"
using namespace std;
using namespace glm;


class Button:public Object{
public:
    
    /**
     button构造函数,使用该构造函数构造对象时，需要使用下面load函数加载着色器和纹理对象，或者使用带有参数的draw函数

     @param pos button初始位置
     @param border button长宽
     */
    Button(vec3 pos,vec2 border);
    
    
    /**
     button构造函数
     
     @param pos button初始位置
     @param border button长宽
     @param shader button着色器
     @param texture button纹理对象
     */
    Button(vec3 pos,vec2 border,shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    
    ~Button();
    
    
    /**
     加载着色器和纹理对象

     @param shader 着色器
     @param texture 纹理对象
     */
    void load(shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    
    
    /**
     绘制button对象
    
     @return 0 == 成功
     */
    GLint draw();
    
    
    /**
     使用传入的着色器和纹理对象绘制button对象，传入的着色器和纹理对象会覆盖现有的资源

     @param shader 着色器
     @param texture 纹理对象
     @return 0 == 成功
     */
    GLint draw(shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    
    
    /**
     移动button位置，目前不需要

     @param deltaTime 移动的时间间隔
     */
    void move(GLfloat deltaTime){};
    
    /**
     根据传入的鼠标坐标，检测按钮是否被按下
     注意：传入的坐标已经经过鼠标坐标系与窗口坐标系的变换
     
     @param xpos 鼠标在窗口内的x轴坐标
     @param ypos 鼠标在窗口内的y轴坐标
     @return true == 按钮被按下
     */
    bool detectPress(double xpos,double ypos);
    
    
    /**
     设置按键按下状态
     */
    void setButtonDown();
    
    /**
     设置按键释放状态
     */
    void setButtonUp();
    
    
    /**
     获取按键状态

     @return true == 保持按下状态
     */
    bool getButtonState();

private:
    VertexArray VAO;
    //设置按钮被按下
    bool isPress;
    //防止按钮被按下时，按键持续缩小
    bool buttonStatus;
    
    vec3 position;
    vec2 bound;
};


#endif /* Button_hpp */
