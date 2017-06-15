//
//  ResourceManager.hpp
//  Game
//
//  Created by txh on 2017/5/31.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "Shader.hpp"
#include "Utility.hpp"

class Texture;

using namespace std;

class ResourceManeger{
public:
    
    /**
     根据顶点着色器脚本和片段着色器脚本生成着色器对象

     @param vertexPath 顶点着色器脚本
     @param fragmentPath 片段着色器脚本
     @param shaderName 着色器对象名称
     @return 着色器对象
     */
    static shared_ptr<Shader> loadShader(string vertexPath,string fragmentPath,string shaderName);
    
    
    /**
     根据着色器名称，获取着色器对象

     @param shaderName 着色器名称
     @return 着色器对象
     */
    static shared_ptr<Shader> getShader(string shaderName);
    
    
    /**
     根据着色器名称，删除着色器对象
     
     @param shaderName 着色器名称
     @return true == 删除成功
     */
    static bool delShader(string shaderName);
    
    
    /**
     根据纹理图片生成纹理对象

     @param texturePath 纹理图片路径
     @param textureName 纹理对象名称
     @param bAlpha 是否是透明图片
     @return 纹理对象
     */
    static shared_ptr<Texture> loadTexture(string texturePath,string textureName,bool bAlpha = false);
    
    
    /**
     根据纹理对象名称，获取纹理对象

     @param textureName 纹理对象名称
     @return 纹理对象
     */
    static shared_ptr<Texture> getTexture(string textureName);
    
    
    /**
     根据纹理对象名称，删除纹理对象
     
     @param shaderName 纹理对象名称
     @return true == 删除成功
     */
    static bool delTexture(string textureName);
    
    //加载字体，仅限DDS文件
    
    /**
     加载字体纹理,目前仅支持DDS文件

     @param font2DPath DDS文件路径
     @param fontName 纹理对象名称
     @return 字体纹理对象
     */
    static shared_ptr<Texture> loadFont2D(string font2DPath,string fontName);
    
    
    /**
     根据纹理对象名称，获取纹理对象
     
     @param textureName 纹理对象名称
     @return 纹理对象
     */
    static shared_ptr<Texture> getFont2D(string fontName);
    
    /**
     根据纹理对象名称，删除纹理对象
     
     @param shaderName 纹理对象名称
     @return true == 删除成功
     */
    static bool delFont2D(string fontName);
    
    
    /**
     清理所有资源

     @return true == 清理成功
     */
    static bool clear();
    
    
private:
    static map<string,shared_ptr<Shader>> shaders;
    static map<string,shared_ptr<Texture>> textures;
    static map<string,shared_ptr<Texture>> fonts;
};
#endif /* ResourceManager_hpp */
