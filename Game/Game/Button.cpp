//
//  Button.cpp
//  Game
//
//  Created by txh on 2017/5/26.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Button.hpp"


Button::Button(vec3 pos,vec2 border)
:position(pos),
bound(border),
buttonStatus(false),
isPress(false)
{
    vertex = Util::getVertexs(bound.x, bound.y);
    model = glm::translate(model, position);
    
    VAO.setBuffer(vertex.get(), 30 * sizeof(GLfloat));
    VAO.setBufferAttrib(0, 3, 5*sizeof(GLfloat), (GLvoid*)0);
    VAO.setBufferAttrib(1, 2, 5*sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

}

Button::Button(vec3 pos,vec2 border,shared_ptr<Shader> shader,shared_ptr<Texture> texture)
:Button(pos,border)
{
    this->shader = shader;
    this->texture = texture;
}

Button::~Button()
{
}

void Button::load(shared_ptr<Shader> shader,shared_ptr<Texture> texture)
{
    this->shader = shader;
    this->texture = texture;
}

GLint Button::draw()
{
    if (shader == nullptr || texture == nullptr) {
        cerr << "ERROR:: shader is nullptr" << endl;
        return -1;
    }
    shader->use();
    
    //当点击按钮，图片缩小，模拟按下
    if (isPress && !buttonStatus) {
        model = glm::scale(model,0.9f * vec3(1.0f,1.0f,1.0f));
        setButtonDown();
    }
    
    shader->setUniformMatrix4fv("model", model);
    shader->setUniformMatrix4fv("trans", trans);
    shader->setUniformMatrix4fv("projection", Util::PROJECTION);
    
    texture->use();
    shader->setUniformSample2D("texture0", 0);
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    VAO.unbind();
    return 0;
}
GLint Button::draw(shared_ptr<Shader> shader,shared_ptr<Texture> texture)
{
    this->shader = shader;
    this->texture = texture;
    return this->draw();
}

bool Button::detectPress(double xpos,double ypos)
{
    //检测鼠标坐标在按键的范围内
    if (fabs(xpos - position.x) < bound.x && fabs(ypos - position.y) < bound.y*1.5) {
        cout << " button press "<< endl;
        isPress = true;
        return true;
    }
    return false;
}

void Button::setButtonDown()
{
    buttonStatus = true;
}
void Button::setButtonUp()
{
    buttonStatus = false;
    isPress = false;
}

bool Button::getButtonState()
{
    return isPress;
}

