//
//  Tube.hpp
//  Game
//
//  Created by txh on 2017/5/25.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Tube_hpp
#define Tube_hpp

#include <stdio.h>
#include <memory>
#include "Object.hpp"
#include "Collision.hpp"
#include "Utility.hpp"
#include "VertexArray.hpp"


using namespace std;
using namespace glm;




class Tube:public Object
{
public:
    
    /**
     tube构造函数

     @param pos tube初始位置
     @param bound tube边长
     @param gap 上下管道间间隔
     */
    Tube(vec3 pos,vec2 bound, GLfloat gap);
    
    
    
    /**
     tube构造函数

     @param pos tube初始位置
     @param bound tube边长
     @param gap 上下管道间间隔
     @param shader tube着色器
     @param texture tube纹理对象
     */
    Tube(vec3 pos,vec2 bound, GLfloat gap,shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    ~Tube();
    
    
    /**
     tube加载新的着色器和纹理对象

     @param shader tube着色器
     @param texture tube纹理器
     */
    void load(shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    
    
    /**
     计算移动矩阵
     
     @param deltaTime 移动时间间隔
     */
    void move(GLfloat deltaTime);
    
    
    /**
     若在构造时或使用load已经传入着色器和纹理对象，则可以直接使用,否则函数直接返回
     
     @return 0 == 成功
     */
    GLint draw();
    
    
    /**
     使用传入的着色器和纹理对象进行绘制，并替换现有着色器和纹理对象，方便下次可以直接使用draw()

     @param shader tube着色器
     @param texture tube纹理器
     @return 0 == 成功
     */
    GLint draw(shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    
    //获取中心点坐标
    /**
     获取上tube的位置坐标，该函数用于检测bird对象与tube对象水平距离

     @return 上tube的位置坐标
     */
    vec2 getPosition();
    
    
    /**
     获取tube的边界长度

     @return 返回tube的边界长度
     */
    vec2 getBound();
    
    
    /**
     获取上tube的碰撞体，用于计算是否发生碰转

     @return 上tube的碰撞体
     */
    RectangleCollision getUpTube() const;
    
    /**
     获取下tube的碰撞体，用于计算是否发生碰转
     
     @return 下tube的碰撞体
     */
    RectangleCollision getDownTube() const;
    
private:
    VertexArray VAO;
    RectangleCollision upRectangleColl;
    RectangleCollision downRectangleColl;
    
};

#endif /* Tube_hpp */
