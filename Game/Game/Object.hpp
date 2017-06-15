//
//  Object.hpp
//  Game
//
//  Created by txh on 2017/5/24.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp


#include <memory>
#include "Physic.hpp"
#include "Collision.hpp"
#include "Utility.hpp"

using namespace std;
using namespace glm;

class Object{
public:
    /**
     构造函数，成员变量初始化
     */
    Object();
    Object(shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    virtual ~Object() = default;
    
    /**
     计算移动矩阵

     @param deltaTime 移动时间间隔
     */
    virtual void move(GLfloat deltaTime) = 0;
    
    
    /**
     若已经初始化好着色器和纹理器，则可以直接绘制
     */
    virtual GLint draw() = 0;
    
    /**
     对象绘制

     @param shader 用于绘制的着色器
     @param texture 用于绘制的纹理对象
     */
    virtual GLint draw(shared_ptr<Shader> shader,shared_ptr<Texture> texture) = 0;
    
protected:
    //顶点坐标
    unique_ptr<GLfloat,Util::ArrayDeletor> vertex;
    mat4 model;
    mat4 zoom;
    mat4 trans;
    shared_ptr<Shader> shader;
    shared_ptr<Texture> texture;
};

#endif /* Object_hpp */
