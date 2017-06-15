//
//  Particle.cpp
//  Game
//
//  Created by txh on 2017/5/27.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Particle.hpp"




ParticleGenerator::Particle::Particle()
:position(vec2(-Util::WINDOW_BORDER.x)),
velocity(vec2(0.0f)),
color(vec4(1.0f)),
life(1.0f)
{

}

ParticleGenerator::Particle::~Particle()
{

}


ParticleGenerator::ParticleGenerator(GLuint count)
:amount(count),
lastUsedNum(0)
{
    GLfloat vertex[] = {
        0.0f,1.0f, 0.0f,1.0f,
        0.0f,0.0f, 0.0f,0.0f,
        1.0f,0.0f, 1.0f,0.0f,
        
        1.0f,0.0f, 1.0f,0.0f,
        1.0f,1.0f, 1.0f,1.0f,
        0.0f,1.0f, 0.0f,1.0f
    };
    
    VAO.setBuffer(vertex, sizeof(vertex));
    VAO.setBufferAttrib(0,4,4*sizeof(GLfloat),(GLvoid*)0);

    
    for (int i = 0; i < amount; ++i) {
        particles.push_back(Particle());
    }
}


ParticleGenerator::ParticleGenerator(GLuint count,shared_ptr<Shader> shader,shared_ptr<Texture> texture)
:ParticleGenerator(count)
{
    this->shader = shader;
    this->texture = texture;
}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::load(shared_ptr<Shader> shader,shared_ptr<Texture> texture)
{
    this->shader = shader;
    this->texture = texture;
}

void ParticleGenerator::update(GLfloat deltaTime,GLuint newParticles ,Bird &object,vec2 offset)
{
    //更新已经死亡的粒子
    for (int i = 0; i < newParticles; ++i) {
        int unused = firstUnusedParticle();
        generatorParticle(particles[unused], object,offset);
    }
    //对所有例子的生命期进行更新以及透明化
    for (int i = 0; i < amount; ++i) {
        Particle &p = particles[i];
        p.life -= deltaTime * Util::PARTICLE_SPEED;
        if (p.life > 0.0f) {
            p.position -= p.velocity * deltaTime;
            p.color.a -= Util::PARTICLE_SPEED * deltaTime;
        }
    }
}


GLint ParticleGenerator::draw()
{
    if (shader == nullptr || texture == nullptr) {
        cerr << "ERROR:: shader or texture is nullptr" << endl;
        return -1;
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader->use();
    shader->setUniformMatrix4fv("projection", Util::PROJECTION);
    
    for (auto p : particles) {
        if (p.life > 0.0) {
            //设置例子偏移
            shader->setUniformVector2f("offset", p.position);
           
            texture->use();
            shader->setUniformVector4f("color", p.color);
            VAO.bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
            VAO.unbind();
        }
    }
    glDisable(GL_BLEND);
    return 0;
}


GLint ParticleGenerator::draw(shared_ptr<Shader> shader,shared_ptr<Texture> texture)
{
    this->shader = shader;
    this->texture = texture;
    return draw();
}

//遍历找到第一个死亡的粒子
GLuint ParticleGenerator::firstUnusedParticle()
{
    for (int i = lastUsedNum; i < amount; ++i) {
        if (particles[i].life <= 0.0f) {
            lastUsedNum = i;
            return i;
        }
    }
    
    for (int i = 0; i < lastUsedNum; ++i) {
        if (particles[i].life <= 0.0f) {
            lastUsedNum = i;
            return i;
        }
    }
    lastUsedNum = 0;
    return 0;
}


//更新已经死亡的粒子
void ParticleGenerator::generatorParticle(Particle &particle,Bird &object,vec2 offset)
{
    default_random_engine e;
    GLfloat random = (e()%100 - 50)/10.0f;
    GLfloat color = 0.5 + (e()%100-50)/100.0f;
    particle.position = object.getposition()+random + offset;
    particle.color = vec4(color,color,color,1.0f);
    particle.life = 1.0f;
    particle.velocity = vec2(1.0f ,object.getVelocity().y) * 0.5f;
}
