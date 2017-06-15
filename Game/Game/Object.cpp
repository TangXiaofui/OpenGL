//
//  Object.cpp
//  Game
//
//  Created by txh on 2017/5/24.
//  Copyright © 2017年 txh. All rights reserved.
//
#include "Object.hpp"


Object::Object()
:shader(nullptr),
texture(nullptr),
vertex(nullptr)
{
    model = trans = glm::translate(trans, vec3(0.0f));
    zoom = glm::scale(zoom, vec3(1.0f));
}


Object::Object(shared_ptr<Shader> shader,shared_ptr<Texture> texture)
:Object()
{
    this->shader = shader;
    this->texture = texture;
}
