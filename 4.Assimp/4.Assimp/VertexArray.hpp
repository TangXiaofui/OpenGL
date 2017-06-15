//
//  VertexArray.hpp
//  Game
//
//  Created by txh on 2017/6/5.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

#include <stdio.h>
#include <GL/glew.h>

class VertexArray{
public:
    /**
     构造函数，生成vaoID号
     
     */
    VertexArray();
    
    /**
     构造函数，生成vaoID号，并用数据初始vao产生的缓存
     
     @param data 数据源
     @param size 数据大小
     */
    VertexArray(GLfloat* data, GLsizeiptr size);
    ~VertexArray();
    
    /**
    向vao产生的内存传入数据

     @param data 数据源
     @param size 数据大小
     @return 0 == 传入成功
     */
    bool setBuffer(const void* data, GLsizeiptr size);
    
    /**
     向vao产生的内存传入索引数据,索引setBuffer的数据
     
     @param data 数据源
     @param size 数据大小
     @return 0 == 传入成功
     */
    bool setElementBuffer(const void* data,GLsizeiptr size);
    
    /**
     对传入vao内存的数据进行设置，说明如何解析该数据

     @param index 指定要修改的顶点属性的索引值，对应脚本layout中的location
     @param size 指定每个顶点属性的组件数量
     @param stride 指定连续顶点属性之间的偏移量
     @param pointer 指定第一个组件在数组的第一个顶点属性中的偏移量
     @return 0 == 设置成功
     */
    bool setBufferAttrib(GLuint index, GLint size,GLsizei stride,const void* pointer);
    
    
    /**
     使用vao绑定的缓存
     */
    void bind();
    
    /**
     解除vao绑定内存
     */
    void unbind();
public:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
};

#endif /* VertexArray_hpp */
