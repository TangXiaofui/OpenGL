//
//  Particle.hpp
//  Game
//
//  Created by txh on 2017/5/27.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
#include <vector>
#include "Object.hpp"
#include "Bird.hpp"
#include <random>


using namespace std;
using namespace glm;


class ParticleGenerator{
public:
    
    /**
     粒子生成器构造函数

     @param count 粒子个数
     */
    ParticleGenerator(GLuint count);
    
    
    /**
     粒子生成器构造函数

     @param count 粒子个数
     @param shader 着色器
     @param texture 纹理对象
     */
    ParticleGenerator(GLuint count,shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    ~ParticleGenerator();
    
    
    /**
     记载着色器和纹理对象

     @param shader 着色器
     @param texture 纹理对象
     */
    void load(shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    
    //更新例子位置，速度，生命期
    /**
     更新粒子位置，速度，生命期

     @param deltaTime 时间间隔
     @param newParticles 新产生的粒子个数
     @param object 粒子群所依附的宿主
     @param offset 粒子偏移量
     */
    void update(GLfloat deltaTime,GLuint newParticles ,Bird &object,vec2 offset = vec2(0.0f,0.0f));
    
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
    
private:
    //内部类，粒子结构
    class Particle {
    public:
        Particle();
        ~Particle();
    public:
        vec2 position;      //位置
        vec2 velocity;      //速度
        vec4 color;
        GLfloat life;       //生命周期
    };
    
    vector<Particle> particles;
    VertexArray VAO;
    shared_ptr<Shader> shader;
    shared_ptr<Texture> texture;
    GLuint amount;
    GLuint lastUsedNum;

    
    /**
     内部函数，用于获取第一个死亡的粒子

     @return 返回第一个死亡的例子
     */
    GLuint firstUnusedParticle();
    
    /**
     内部函数，产生新的粒子

     @param particle 已经死亡的例子
     @param object 粒子群所依附的宿主
     @param offset 粒子偏移量
     */
    void generatorParticle(Particle &particle,Bird &object,vec2 offset = vec2(0.0f,0.0f));

};



#endif /* Particle_hpp */
