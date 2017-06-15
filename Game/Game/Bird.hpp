//
//  Bird.hpp
//  Game
//
//  Created by txh on 2017/5/31.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Bird_hpp
#define Bird_hpp

#include <memory>
#include "Physic.hpp"
#include "Collision.hpp"
#include "Tube.hpp"
#include "Object.hpp"
#include "Utility.hpp"
#include "VertexArray.hpp"

using namespace std;
using namespace glm;

class Bird:public Object,public CircleCollision{
public:
    
    /**
     构造函数

     @param pos 初始位置
     @param scale 缩放比例
     */
    Bird(vec2 pos, vec2 scale = vec2(1.0f,1.0f));
    
    /**
     构造函数

     @param pos 初始位置
     @param shader 着色器
     @param texture 纹理对象
     @param scale 缩放比例
     */
    Bird(vec2 pos, shared_ptr<Shader> shader, shared_ptr<Texture> texture, vec2 scale = vec2(1.0f,1.0f));
    
    ~Bird();
    
    
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
     
     @param shader 着色器
     @param texture 纹理器å
     @return 0 == 成功
     */
    GLint draw(shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    
    /**
     加载着色器和纹理对象
     
     @param shader 着色器
     @param texture 纹理对象
     */
    void load(shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    
    
    /**
     与tube检测是否发生碰撞

     @param tube tube对象
     @return true == 发生碰撞
     */
    bool detectCollision(const Tube &tube);
    
    
    /**
     获取bird位置

     @return bird 位置
     */
    vec2 getposition();
    
    
    
    /**
     获取bird半径，用于碰撞检测

     @return bird半径
     */
    GLfloat getRadius();
    
private:
    VertexArray VAO;
};

#endif /* Bird_hpp */
