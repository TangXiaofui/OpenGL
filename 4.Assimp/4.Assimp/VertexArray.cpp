//
//  VertexArray.cpp
//  Game
//
//  Created by txh on 2017/6/5.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "VertexArray.hpp"



VertexArray::VertexArray()
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
}

VertexArray::VertexArray(GLfloat* data, GLsizeiptr size)
:VertexArray()
{
    
}
VertexArray::~VertexArray()
{
    glDeleteBuffers(1,&EBO);
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
}

bool VertexArray::setBuffer(const void* data, GLsizeiptr size)
{
    if (data == NULL) {
        return false;
    }
    this->bind();
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW);
    this->unbind();
    return true;
}

bool VertexArray::setElementBuffer(const void* data,GLsizeiptr size)
{
    if (data == NULL) {
        return false;
    }
    this->bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    this->unbind();
    return true;
}

bool VertexArray::setBufferAttrib(GLuint index, GLint size,GLsizei stride,const void* pointer)
{
    this->bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    this->unbind();
    return true;
}

void VertexArray::bind()
{
    glBindVertexArray(this->VAO);
}
void VertexArray::unbind()
{
    glBindVertexArray(0);
}
