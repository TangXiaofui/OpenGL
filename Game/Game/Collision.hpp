//
//  Collision.hpp
//  Game
//
//  Created by txh on 2017/5/25.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Collision_hpp
#define Collision_hpp

#include <glm/glm.hpp>
using namespace glm;


//碰撞物体的轮廓
enum CollisionType{
    Rectangle,
    Circle
};

class Collision{
public:
    
    /**
     碰撞体构造函数，初始化成员对象
    */
    Collision();
    virtual ~Collision() = default;
    
    
    /**
     纯虚函数，可以根据不同形状的物体实现不同的碰转检测机制

     @param rh 用于检测碰撞的物体
     @return true == 发生碰撞
     */
    virtual bool detectCollide(const Collision &rh) = 0;
    
    
    
    /**
     设置碰撞体位置

     @param pos 2维位置信息
     */
    void setPosition(vec2 &pos);
    
    
    /**
     设置碰撞体速度

     @param velo 2维速度信息
     */
    void setVelocity(vec2 &velo);
    
    
    /**
     设置碰撞体边长

     @param b 2维边长信息
     */
    void setBound(vec2 &b);
    
    
    
    /**
     若碰撞体是圆，则设置其半径

     @param r 碰撞体半径
     */
    void setRadius(float &r);
    
    
    /**
     获取碰撞体位置信息

     @return 碰撞体2维位置信息
     */
    vec2 getPosition() const;
    
    /**
     获取碰撞体速度信息
     
     @return 碰撞体2维速度信息
     */
    vec2 getVelocity() const;
    
    /**
     获取碰撞体边长信息
     
     @return 碰撞体2维边长信息
     */
    vec2 getBound() const;
    
    /**
     获取碰撞体半径信息
     
     @return 碰撞体半径信息
     */
    float getRadius() const;
    
    /**
     获取碰撞体类型

     @return 碰撞体类型
     */
    CollisionType getType() const;
    
    /**
     移动碰撞体位置

     @param offset 2维碰撞体移动量
     */
    void addPosition(const vec2 &offset);
    
    /**
     修改碰撞体移动速度
     
     @param offset 2维碰撞体移动速度量
     */
    void addVelocity(const vec2 &offset);
    
protected:
    vec2 position;              //中点位置坐标
    vec2 velocity;
    vec2 bound;                 //物体 长度以及宽度
    float radius;
    CollisionType type;
    
};

class CircleCollision:public Collision{
public:
    CircleCollision(float xpos,float ypos,float r);
    virtual ~CircleCollision();
    
    
    /**
     与碰撞体的碰撞检测

     @param rh 碰撞体
     @return true == 发生碰撞
     */
    bool detectCollide(const Collision &rh);
    
};

//矩形碰撞体
class RectangleCollision:public Collision{
public:
    RectangleCollision(float xpos,float ypos,float xbound,float ybound);
    virtual ~RectangleCollision();
    
    
    /**
     与碰撞体的碰撞检测
     
     @param rh 碰撞体
     @return true == 发生碰撞
     */
    bool detectCollide(const Collision &rh);
};

#endif /* Collision_hpp */
