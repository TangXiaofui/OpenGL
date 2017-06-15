//
//  Tube.cpp
//  Game
//
//  Created by txh on 2017/5/25.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Tube.hpp"

//获取上下tube顶点坐标
unique_ptr<GLfloat,Util::ArrayDeletor> getVertexs(GLfloat width,GLfloat height,GLfloat gap)
{
    return unique_ptr<GLfloat,Util::ArrayDeletor>(new GLfloat[5 * 12]{
        //cood                                      //tex
        -width,  height + gap,     0.0f,        0.0f,1.0f,
        -width,  gap,              0.0f,        0.0f,0.0f,
         width,  gap,              0.0f,        1.0f,0.0f,
         width,  gap,              0.0f,        1.0f,0.0f,
         width,  height + gap,     0.0f,        1.0f,1.0f,
        -width,  height + gap,     0.0f,        0.0f,1.0f,
        
        -width, -gap,              0.0f,        0.0f,-1.0f,
        -width, -height - gap,     0.0f,        0.0f, 0.0f,
         width, -height - gap,     0.0f,        1.0f, 0.0f,
         width, -height - gap,     0.0f,        1.0f, 0.0f,
         width, -gap,              0.0f,        1.0f,-1.0f,
        -width, -gap,              0.0f,        0.0f,-1.0f
    });
}


Tube::Tube(vec3 pos,vec2 bound,GLfloat gap)
:upRectangleColl(pos[0],  pos[1]+bound.y/2 + gap,  bound.x,  bound.y/2),
downRectangleColl(pos[0], pos[1]-bound.y/2 - gap,  bound.x,  bound.y/2)
{
    vertex = getVertexs(bound.x,bound.y,gap);
    model = glm::translate(model, pos);
    
    VAO.setBuffer(vertex.get(), 5 * 12 * sizeof(GLfloat));
    VAO.setBufferAttrib(0, 3, 5 * sizeof(GLfloat), (GLvoid*)0);
    VAO.setBufferAttrib(1, 2, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    
}

//使用c++11委托构造函数，增加代码复用
Tube::Tube(vec3 pos,vec2 bound,GLfloat gap,shared_ptr<Shader> shader,shared_ptr<Texture> texture)
:Tube(pos,bound,gap)
{
    this->shader = shader;
    this->texture = texture;
}


Tube::~Tube()
{
}


void Tube::load(shared_ptr<Shader> shader,shared_ptr<Texture> texture)
{
    this->shader = shader;
    this->texture = texture;
}

void Tube::move(GLfloat deltaTime)
{
    //图像移动
    trans = glm::translate(trans,Util::TUBE_SPEED*deltaTime * vec3(-1.0f,0.0f,0.0f));
    vec2 pos = vec2();
    //碰撞体移动
    pos.x -= Util::TUBE_SPEED * deltaTime;
    upRectangleColl.addPosition(pos);
    downRectangleColl.addPosition(pos);

}

GLint Tube::draw()
{
    if (shader == nullptr || texture == nullptr) {
        cerr << "ERROR:: shader is nullptr" << endl;
        return -1;
    }
    
    shader->use();
    shader->setUniformMatrix4fv("model", model);
    shader->setUniformMatrix4fv("trans", trans);
    shader->setUniformMatrix4fv("projection", Util::PROJECTION);
    
    if (texture != nullptr) {
         texture->use();
         shader->setUniformSample2D("texture0", 0);
    }
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 5*12/3);
    VAO.unbind();
    return 0;
}
GLint Tube::draw(shared_ptr<Shader> shader,shared_ptr<Texture> texture)
{
    this->shader = shader;
    this->texture = texture;
    return this->draw();
}

//由于只要x轴坐标，因此上下管道随意选一个
vec2 Tube::getPosition()
{
    return upRectangleColl.getPosition();
}

vec2 Tube::getBound()
{
    return upRectangleColl.getBound();
}

//获取上tube
RectangleCollision Tube::getUpTube() const
{
    return upRectangleColl;
}
//获取下tube
RectangleCollision Tube::getDownTube() const
{
    return downRectangleColl;
}
