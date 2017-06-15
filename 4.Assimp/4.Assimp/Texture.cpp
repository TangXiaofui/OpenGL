//
//  Texture.cpp
//  Game
//
//  Created by txh on 2017/5/25.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Texture.hpp"

Texture::Texture()
:textureID(0)
{
    glGenTextures(1, &textureID);
    setTextureParam(GL_REPEAT,GL_REPEAT,GL_LINEAR,GL_LINEAR);
}


Texture::Texture(GLuint id, string type,aiString path)
:Texture()
{
    this->textureID = id;
    this->type = type;
    this->path = path;
}

Texture::Texture(unsigned char* data,int width,int height, bool bAlpha)
:Texture()
{
    assert(data != NULL);
    load(data, width, height, bAlpha);
}
Texture::Texture(unsigned char *buffer, GLuint mipMapCount, GLuint width, GLuint height, GLuint blockSize, GLuint format)
:Texture()
{
    assert(buffer != NULL);
    load(buffer, mipMapCount, width, height, blockSize, format);
}

Texture::~Texture()
{
    //mesh 和 model里面使用了texture临时变量，导致刚加载的纹理马上就被释放掉，
//    if (textureID) {
//        glDeleteTextures(1, &textureID);
//    }
}

GLint Texture::load(unsigned char* data,int width,int height, bool bAlpha)
{
    if (data == NULL) {
        cerr << "ERROR::Texture data is NULL." << endl;
        return -1;
    }
    this->bAlpha = bAlpha;
    
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 bAlpha ? GL_RGBA : GL_RGB,
                 width,
                 height,
                 0,
                 bAlpha ? GL_RGBA : GL_RGB,
                 GL_UNSIGNED_BYTE,
                 data);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    return 0;
}


GLint Texture::load(unsigned char *buffer, GLuint mipMapCount, GLuint width, GLuint height, GLuint blockSize, GLuint format)
{
    if (buffer == NULL) {
        cerr << "ERROR::Texture data is NULL." << endl;
        return -1;
    }
    
    GLuint offset = 0;
   
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    for (GLuint level = 0; level < mipMapCount && (width || height); ++level)
    {
        GLuint size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                               0, size, buffer + offset);
        
        offset += size;
        width  /= 2;
        height /= 2;
        
        if(width < 1) width = 1;
        if(height < 1) height = 1;
    }
    
    return 0;
}

GLint Texture::setTextureParam(GLint wrapSParam, GLint wrapTParam, GLint MagFilterParm, GLint MinFilterParm)
{
    this->wrapSParam = wrapSParam;
    this->wrapTParam = wrapTParam;
    this->MagFilterParm = MagFilterParm;
    this->MinFilterParm = MinFilterParm;
    glBindTexture(GL_TEXTURE_2D, textureID);
    //设置环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapSParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapTParam);
    //设置过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilterParm);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilterParm);
    glBindTexture(GL_TEXTURE_2D, 0);
    return 0;
}

GLint Texture::use(int index)
{
    if (textureID == 0) {
        cerr << "ERROR:: textureID is NULL"<< endl;
        return -1;
    }
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, textureID);
    return 0;
}

string Texture::getType()
{
    return this->type;
}
aiString Texture::getPath()
{
    return this->path;
}
GLuint Texture::getID()
{
    return this->textureID;
}
