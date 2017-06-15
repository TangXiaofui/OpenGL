//
//  Font2D.hpp
//  Game
//
//  Created by txh on 2017/5/26.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Font2D_hpp
#define Font2D_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.hpp"
#include "Texture.hpp"
#include <string>
#include "VertexArray.hpp"
using namespace std;
using namespace glm;

class Texture;

class Font2D{
public:
    
    /**
     构造函数，使用该构造函数，需要手动调用load函数加载着色器和纹理对象
     */
    Font2D();
    
    /**
     font构造函数

     @param shader font着色器
     @param texture font纹理对象
     */
    Font2D(shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    
    ~Font2D();
    
    
    /**
     加载着色器和纹理对象
     
     @param shader font着色器
     @param texture font纹理对象
     */
    void load(shared_ptr<Shader> shader,shared_ptr<Texture> texture);
    
    /**
     将传入的字符串绘制到窗口中

     @param text 需要绘制的字符串
     @param x 字符串在窗口X坐标
     @param y 字符串在窗口Y坐标
     @param size 每个字符大小
     @param uniformSampler 纹理对象层
     @return 0 == 绘制成功
     */
    GLint printText2D(const char * text, int x, int y, int size, string uniformSampler);
    
private:
    VertexArray VAO;
    shared_ptr<Shader> shader;
    shared_ptr<Texture> texture;
};

#endif /* Font2D_hpp */
