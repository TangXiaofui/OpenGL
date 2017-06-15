//
//  ResourceManager.cpp
//  Game
//
//  Created by txh on 2017/5/31.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "ResourceManager.hpp"
#include "Texture.hpp"

map<string,shared_ptr<Shader>> ResourceManeger::shaders;
map<string,shared_ptr<Texture>> ResourceManeger::textures;
map<string, shared_ptr<Texture>> ResourceManeger::fonts;


shared_ptr<Shader> ResourceManeger::loadShader(string vertexPath,string fragmentPath,string shaderName)
{
    if (vertexPath.size() == 0 || fragmentPath.size() == 0 || shaderName.size() == 0) {
        cerr << "vertex or fragment or name is NULL" << endl;
        return shared_ptr<Shader>();
    }
    //首先从缓存中搜索，找到即返回，否则创建着色器
    if (shaders.find(shaderName) != shaders.end()) {
        return shaders[shaderName];
    }
    else{
        Util::processFilePath(vertexPath);
        Util::processFilePath(fragmentPath);
        
        shared_ptr<Shader> shader(new Shader);
        string strVertex,strFragment;
        ifstream vertexFile,fragmentFile;
        vertexFile.exceptions(ifstream::badbit);
        fragmentFile.exceptions(ifstream::badbit);
        
        try {
            stringstream vertexCode;
            stringstream fragCode;
            
            vertexFile.open(vertexPath);
            fragmentFile.open(fragmentPath);
            vertexCode << vertexFile.rdbuf();
            fragCode << fragmentFile.rdbuf();
            
            vertexFile.close();
            fragmentFile.close();
            
            strVertex = vertexCode.str();
            strFragment = fragCode.str();
        
        } catch (ifstream::failure e) {
            cout << "ERROR :: Failed to open script" << endl;
        }
        
        const GLchar *vCode = strVertex.c_str();
        const GLchar *fCode = strFragment.c_str();
        GLint ret = shader->load(vCode, fCode);
        if (ret != 0) {
            return shared_ptr<Shader>();
        }
        else
        {
            shaders[shaderName] = shader;
            return shader;
        }
    }
}

shared_ptr<Shader> ResourceManeger::getShader(string shaderName)
{
    return shaders[shaderName];
}

bool ResourceManeger::delShader(string shaderName)
{
    return shaders.erase(shaderName) > 0;
}

shared_ptr<Texture> ResourceManeger::loadTexture(string texturePath,string textureName,bool bAlpha)
{
    if (texturePath.size() == 0 || textureName.size() == 0) {
        cerr << "texture or  name is NULL" << endl;
        return shared_ptr<Texture>();
    }
    if (textures.find(textureName) != textures.end()) {
        return textures[textureName];
    }
    else{
        Util::processFilePath(texturePath);
        
        shared_ptr<Texture> texture(new Texture);
        int width,height;
        unsigned char *data = SOIL_load_image(texturePath.c_str(), &width, &height, NULL,
                                              bAlpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
        texture->load(data,width,height,bAlpha);
        SOIL_free_image_data(data);
        
        textures[textureName] = texture;
        return texture;
    }
}

shared_ptr<Texture> ResourceManeger::getTexture(string textureName)
{
    return textures[textureName];
}

bool ResourceManeger::delTexture(string textureName)
{
    return textures.erase(textureName) > 0;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

shared_ptr<Texture> ResourceManeger::loadFont2D(string font2DPath,string fontName)
{
    if (font2DPath.size() == 0 || fontName.size() == 0) {
        cerr << "font2D or name is NULL" << endl;
        return shared_ptr<Texture>();
    }
    if (fonts.find(fontName) != fonts.end()) {
        return fonts[fontName];
    }
    else{
        Util::processFilePath(font2DPath);
        
        unsigned char header[124];
        FILE *fp;
        fp = fopen(font2DPath.c_str(), "rb");
        if (fp == NULL){
            printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", font2DPath.c_str()); getchar();
            return 0;
        }
        
        char filecode[4];
        fread(filecode, 1, 4, fp);
        if (strncmp(filecode, "DDS ", 4) != 0) {
            fclose(fp);
            return 0;
        }
        
        fread(&header, 124, 1, fp);
        
        unsigned int height      = *(unsigned int*)&(header[8 ]);
        unsigned int width	     = *(unsigned int*)&(header[12]);
        unsigned int linearSize	 = *(unsigned int*)&(header[16]);
        unsigned int mipMapCount = *(unsigned int*)&(header[24]);
        unsigned int fourCC      = *(unsigned int*)&(header[80]);
        
        
        unsigned char * buffer;
        unsigned int bufsize;
        bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
        buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
        fread(buffer, 1, bufsize, fp);
        fclose(fp);

        unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
        unsigned int format;
        switch(fourCC)
        {
            case FOURCC_DXT1:
                format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                break;
            case FOURCC_DXT3:
                format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                break;
            case FOURCC_DXT5:
                format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                break;
            default:
                free(buffer);
                return 0;
        }
        
        unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
        unsigned int offset = 0;
        
        shared_ptr<Texture> texture(new Texture);
        texture->load(buffer, mipMapCount,  width, height, blockSize, format);
        
        free(buffer);
        
        fonts[fontName] = texture;

        return texture;
    }
}

shared_ptr<Texture> ResourceManeger::getFont2D(string fontName)
{
    return fonts[fontName];
}

bool ResourceManeger::delFont2D(string fontName)
{
    return fonts.erase(fontName) > 0;
}

bool ResourceManeger::clear()
{
    shaders.clear();
    textures.clear();
    fonts.clear();
    
    return true;
}
