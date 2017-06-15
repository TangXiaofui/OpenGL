//
//  Shader.hpp
//  2.2indexVertex
//
//  Created by txh on 2017/5/22.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;


class Shader{
public:
    
    Shader();
    Shader(const char* vCode,const char *fCode);
    ~Shader();

    /**
     使用shader

     @return 0 == 成功
     */
    GLint use();
    
    
    /**
     编译链接顶点着色器和片段着色器

     注意：不能传入文件路径名，需要传入脚本文件内容
     @param vCode 顶点着色器脚本内容
     @param fCode 片段着色器脚本内容
     @return 返回编译连接生成的着色器id, 返回值 >0 成功
     */
    GLint load(const char *vCode,const char *fCode);
    
    
    /**
     向着色器传入mat4参数

     @param uniform 着色器内mat4参数的变量名称
     @param matrix 需要传入的mat4参数
     @param useShader 是否使用着色器
     @return true == 传入成功
     */
    bool setUniformMatrix4fv(const char* uniform,mat4 matrix, GLboolean useShader = true );
    
    /**
     向着色器传入vec2参数
     
     @param uniform 着色器内vec2参数的变量名称
     @param vec 需要传入的vec2参数
     @param useShader 是否使用着色器
     @return true == 传入成功
     */
    bool setUniformVector2f(const char* uniform,vec2 vec,GLboolean useShader = true);
    
    
    /**
     向着色器传入vec4参数
     
     @param uniform 着色器内vec4参数的变量名称
     @param vec 需要传入的vec4参数
     @param useShader 是否使用着色器
     @return true == 传入成功
     */
    bool setUniformVector4f(const char* uniform,vec4 vec,GLboolean useShader = true);
    
    /**
     向着色器传入纹理层

     @param uniform 着色器内纹理的名称
     @param layout 着色器内第layout层纹理
     @return true == 传入成功
    */
    bool setUniformSample2D(const char* uniform,GLint layout,GLboolean useShader = true);

    
private:
    GLuint programID;
};
#endif /* Shader_hpp */
