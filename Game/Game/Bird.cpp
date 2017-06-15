//
//  Bird.cpp
//  Game
//
//  Created by txh on 2017/5/31.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Bird.hpp"


Bird::Bird(vec2 pos,vec2 scale):
CircleCollision(pos.x,pos.y,scale.x)
{
    vertex = Util::getVertexs(scale.x,scale.y);
    model = glm::translate(model,vec3(CircleCollision::getPosition().x,0.0f,0.0f));
    
    VAO.setBuffer(vertex.get(), 30 * sizeof(GLfloat));
    VAO.setBufferAttrib(0, 3, 5 * sizeof(GLfloat), (GLvoid*)0);
    VAO.setBufferAttrib(1, 2, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));

}

Bird::Bird(vec2 pos, shared_ptr<Shader> shader, shared_ptr<Texture> texture, vec2 scale)
:Bird(pos,scale)
{
    this->shader = shader;
    this->texture = texture;
}


Bird::~Bird()
{
}


void Bird::load(shared_ptr<Shader> shader,shared_ptr<Texture> texture)
{
    this->shader = shader;
    this->texture = texture;
}



void Bird::move(GLfloat deltaTime)
{
    vec2 pos = vec2();
    if (CircleCollision::getPosition().x <= 0.0f) {
        pos.x += Util::BIRD_HORIZON_VELOCITY;
        model = glm::translate(model, vec3(pos,0.0f));          //水平方向
    }
    vec2 velo = vec2(0.0f);
    model = glm::translate(model, vec3(0.0f,1.0f * Physic::getDistance(CircleCollision::getVelocity().y,deltaTime),0.0f));    //竖直方向
    pos.y += Physic::getDistance(CircleCollision::getVelocity().y,deltaTime);
    velo.y = Physic::getVelocity(CircleCollision::getVelocity().y, deltaTime);
    CircleCollision::setVelocity(velo);                  //更新速度
    CircleCollision::addPosition(pos);
}



GLint Bird::draw()
{
    if (shader == nullptr || texture == nullptr) {
        cerr << "ERROR:: shader is nullptr" << endl;
        return -1;
    }
    shader->use();
    shader->setUniformMatrix4fv("model", model);
    shader->setUniformMatrix4fv("trans", trans);
    shader->setUniformMatrix4fv("projection", Util::PROJECTION);
    
    texture->use();
    
    shader->setUniformSample2D("texture0", 0);
    
    VAO.bind();
    glDisable(GL_BLEND);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    VAO.unbind();
    return 0;
}

GLint Bird::draw(shared_ptr<Shader> shader,shared_ptr<Texture> texture)
{
    this->shader = shader;
    this->texture = texture;
    return this->draw();
}

bool Bird::detectCollision(const Tube &tube)
{
    return CircleCollision::detectCollide(tube.getUpTube()) || CircleCollision::detectCollide(tube.getDownTube());
}


vec2 Bird::getposition()
{
    return CircleCollision::getPosition();
}


GLfloat Bird::getRadius()
{
    return CircleCollision::getRadius();
}
