//
//  Texture.hpp
//  Game
//
//  Created by txh on 2017/5/25.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "ResourceManager.hpp"

using namespace glm;


class Texture{
public:
    
    
    /**
     构造函数，使用该构造函数时，必须使用下面load函数，手动加载纹理数据
     */
    Texture();
    Texture(unsigned char* data,int width,int height, bool bAlpha);
    Texture(unsigned char *buffer, GLuint mipMapCount, GLuint width, GLuint height, GLuint blockSize, GLuint format);
    ~Texture();
    
    
    /**
     使用纹理对象

     @param index 纹理层
     @return 0 == 调用成功
     */
    GLint use(int index = 0);
    
    
    /**
     设置纹理参数

     @param wrapSParam s轴环绕参数
     @param wrapTParam t轴环绕参数
     @param MagFilterParm 放大过滤参数
     @param MinFilterParm 缩小过滤参数
     @return 0 == 调用成功
     */
    GLint setTextureParam(GLint wrapSParam, GLint wrapTParam, GLint MagFilterParm, GLint MinFilterParm);
    
    
    /**
     加载纹理数据

     @param data 数据源,该数据经第三方库函数SOIL处理后传入
     @param width 纹理宽度
     @param height 纹理高度
     @param bAlpha 是否透明度
     @return 0 == 调用成功
     */
    GLint load(unsigned char* data,int width,int height, bool bAlpha);
    
    
    /**
     加载纹理数据,针对DDS文件

     @param buffer 数据源
     @param mipMapCount 细节级别数
     @param width 纹理宽度
     @param height 纹理高度
     @param blockSize 压缩图像纹理大小
     @param format 数据源存储格式
     @return 0 == 调用成功
     */
    GLint load(unsigned char *buffer, GLuint mipMapCount, GLuint width, GLuint height, GLuint blockSize, GLuint format);
private:
    GLuint textureID;
    bool bAlpha;
    GLint wrapSParam;
    GLint wrapTParam;
    GLint MagFilterParm;
    GLint MinFilterParm;
};

#endif /* Texture_hpp */
