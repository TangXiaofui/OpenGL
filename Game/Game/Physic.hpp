//
//  Physic.hpp
//  Game
//
//  Created by txh on 2017/5/24.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Physic_hpp
#define Physic_hpp


#include "Utility.hpp"

class Physic
{
public:
    
    /**
     根据牛顿定理计算在y轴方向的位移

     @param v0 y轴方向初始速度
     @param deltaTime 运动持续时间
     @return y轴方向运动距离
     */
    static float getDistance(float v0,float deltaTime)
    {
        return v0 * deltaTime - 0.5 * Util::GRAVITY * deltaTime * deltaTime;
    }
    
    
    /**
     重力加速度的作用下，y轴方向速度的变化

     @param v0 y轴方向速度
     @param deltaTime 变化持续时间
     @return y轴方向运动速度
     */
    static float getVelocity(float v0,float deltaTime)
    {
        return v0 - Util::GRAVITY * deltaTime;
    }
    
    Physic() = delete;
    ~Physic() = delete;
    Physic(const Physic &) = delete;
    Physic(Physic &&) = delete ;
    Physic& operator = (const Physic&) = delete;
    Physic& operator = (Physic && ) = delete ;
    
};

#endif /* Physic_hpp */
