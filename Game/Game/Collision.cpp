//
//  Collision.cpp
//  Game
//
//  Created by txh on 2017/5/25.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Collision.hpp"
#include <cmath>
#include <ctgmath>
#include <math.h>

Collision::Collision()
:position(vec2(0.0f)),
velocity(vec2(0.0f))
{

}

void Collision::setPosition(vec2 &pos)
{
    this->position = pos;
}

void Collision::setVelocity(vec2 &velo)
{
    this->velocity = velo;
}

void Collision::setBound(vec2 &b)
{
    this->bound = b;
}

void Collision::setRadius(float &r)
{
    this->radius = r;
}

vec2 Collision::getPosition() const
{
    return this->position;
}

vec2 Collision::getVelocity() const
{
    return this->velocity;
}

vec2 Collision::getBound() const
{
    return this->bound;
}

float Collision::getRadius() const
{
    return this->radius;
}

CollisionType Collision::getType() const
{
    return this->type;
}

void Collision::addPosition(const vec2 &offset)
{
    this->position += offset;
}

void Collision::addVelocity(const vec2 &offset)
{
    this->velocity += offset;
}





CircleCollision::CircleCollision(float xpos,float ypos,float r)
{
    type = Circle;
    position = vec2(xpos,ypos);
    this->radius = r;
}


CircleCollision::~CircleCollision()
{

}

bool CircleCollision::detectCollide(const Collision &rh)
{
    if (rh.getType() == Circle) {
        //...当碰撞体是圆时
    }
    else if(rh.getType() == Rectangle){
        //使用勾股定理计算两个碰撞体中点距离
        float xLength = fabs(this->getPosition().x - rh.getPosition().x);
        float yLength = fabs(this->getPosition().y - rh.getPosition().y);
        float distance = sqrt(xLength*xLength + yLength * yLength);
        
        //使用等比三角形求出矩形中心到边界距离
        float x;
        if ((xLength / yLength) <= (rh.getBound().x / rh.getBound().y)) {
            x = distance * rh.getBound().y / yLength;
        }
        else{
            x = distance * rh.getBound().x / xLength;
        }
        
        //当边界距离加圆半径大于碰撞体之间的距离时，碰撞发生
        if (x + this->radius >= distance) {
            return true;
        }
        else
            return false;
        
    }
    return false;
}





RectangleCollision::RectangleCollision(float xpos,float ypos,float xbound,float ybound)
{
    type = Rectangle;
    this->position = vec2(xpos,ypos);
    this->bound = vec2(xbound,ybound);
}

RectangleCollision::~RectangleCollision()
{

}

bool RectangleCollision::detectCollide(const Collision &rh)
{
    
    if (rh.getType() == Circle) {
        
    }
    else{
        int x;
        //先比较中心点相对位置，然后在比较左矩形的右边界 与 右矩形的左边界的相对距离
        if (this->getPosition().x < rh.getPosition().x) {
            x = this->getPosition().x + this->getBound().x / 2 - (rh.getPosition().x - rh.getBound().x/2);
        }
        else
        {
            x = rh.getPosition().x + rh.getBound().x / 2  - (this->getPosition().x - this->getBound().x/2);
        }
        
        //x坐标没有交叉，不可能发生碰撞
        if (x < 0) {
            return false;
        }
    
        //x坐标交叉的前提下，计算y是否交叉
    
        int y;
        if (this->getPosition().y < rh.getPosition().y) {
            y = this->getPosition().y + this->getBound().y / 2 - (rh.getPosition().y - rh.getBound().y / 2);
        }
        else
        {
            y = rh.getPosition().y + rh.getBound().y / 2 - (this->getPosition().y - this->getBound().y /2 );
        }
    
        if (y < 0) {
            return false;
        }
        else
            return true;
        }
    return false;
}
