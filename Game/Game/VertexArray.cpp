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
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
}

VertexArray::VertexArray(GLfloat* data, GLsizeiptr size)
:VertexArray()
{
    
}
VertexArray::~VertexArray()
{
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
}

bool VertexArray::setBuffer(const void* data, GLsizeiptr size)
{
    if (data == NULL) {
        return false;
    }
    this->bind();
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,size ,data,GL_STATIC_DRAW);
    this->unbind();
    return true;
}

bool VertexArray::setBufferAttrib(GLuint index, GLint size,GLsizei stride,const void* pointer)
{
    this->bind();
    glVertexAttribPointer(index,size,GL_FLOAT,GL_FALSE,stride,pointer);
    glEnableVertexAttribArray(index);
    
    this->unbind();
    return true;
}

void VertexArray::bind()
{
    glBindVertexArray(VAO);
}
void VertexArray::unbind()
{
    glBindVertexArray(0);
}
