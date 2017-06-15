//
//  Utility.hpp
//  Game
//
//  Created by txh on 2017/6/3.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Utility_hpp
#define Utility_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.hpp"
#include "Texture.hpp"
using namespace std;
using namespace glm;

namespace Util {


/**
 路径字符串处理，支持相对路径以及绝对路径

 @param filepath 需要处理的字符串,引用
 */
extern void processFilePath(string &filepath);

    
class ArrayDeletor{
public:
    ArrayDeletor():count(0){}
    
    void operator()(GLfloat *p){
        delete [] p;
    }
public:
    int count;
};

    
/**
 根据传入的长度和宽度，获取顶点位置坐标

 @param width 矩形长度
 @param height 矩形宽度
 @return 顶点位置坐标向量
 */
extern unique_ptr<GLfloat,ArrayDeletor> getVertexs(GLfloat width,GLfloat height);
  

    
//窗口边界
extern const vec2 WINDOW_BORDER;
//正交投影
extern const mat4 PROJECTION;
//按键位置映射
extern const mat3 TRANS;

//重力加速度
extern float GRAVITY;
//当点击空格键时，设置bird的垂直速度
extern float BIRD_VERTICAL_VELOCITY;
//bird水平移动速度
extern float BIRD_HORIZON_VELOCITY;
    
//tube移动速度
extern float TUBE_SPEED;
    
//particle速度参数
extern float PARTICLE_SPEED;

}

#endif /* Utility_hpp */
