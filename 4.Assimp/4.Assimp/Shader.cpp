//
//  Shader.cpp
//  2.2indexVertex
//
//  Created by txh on 2017/5/22.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

Shader::Shader()
:programID(0)
{

}

Shader::Shader(const char* vCode,const char *fCode)
:programID(0)
{
    assert(vCode != NULL);
    assert(fCode != NULL);
    load(vCode, fCode);
}

Shader::~Shader()
{
    if (programID) {
        glDeleteProgram(programID);
    }
}

GLint Shader::load(const char *vCode,const char *fCode)
{
    if (vCode == NULL || fCode == NULL) {
        cerr << "shader or fragment code is null" << endl;
        return 0;
    }
    
    //若一个已经存在的着色器再次load，则关闭原先的，在重新编译连接生成新的shader id
    if (programID) {
        glDeleteProgram(programID);
    }
    
    //编译顶点着色器
    char buf[512];
    GLint success;
    GLuint vertexID,fragmentID;
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID,1,&vCode,NULL);
    glCompileShader(vertexID);
    glGetShaderiv(vertexID,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(vertexID,sizeof(buf),NULL,buf);
        cout << "ERROR :: compile vertex shader failed. " << buf  <<endl;
    }
    
    //编译片段着色器
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID,1,&fCode,NULL);
    glCompileShader(fragmentID);
    glGetShaderiv(fragmentID,GL_COMPILE_STATUS,&success);
    
    if (!success) {
        glGetShaderInfoLog(fragmentID,sizeof(buf),NULL,buf);
        cout << "ERROR :: compile fragment shader failed. "<< buf << endl;
    }
    
    //链接程序
    programID = glCreateProgram();
    glAttachShader(programID,vertexID);
    glAttachShader(programID,fragmentID);
    glLinkProgram(programID);
    glGetProgramiv(programID,GL_LINK_STATUS,&success);
    if (!success) {
        glGetProgramInfoLog(programID,sizeof(buf),NULL,buf);
        cout << "ERROR :: Link shader failed " << endl;
    }
    
    //清理资源
    glDetachShader(programID,vertexID);
    glDetachShader(programID,fragmentID);
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
    
    return 0;
}

GLint Shader::use()
{
    glUseProgram(programID);
    return 0;
}

bool Shader::setUniformMatrix4fv(const char* uniform,mat4 matrix, GLboolean useShader)
{
    if (uniform == NULL) {
        cerr << "uniform is NULL" << endl;
        return false;
    }
    if (useShader) {
        use();
    }
    glUniformMatrix4fv(glGetUniformLocation(programID,uniform),1,GL_FALSE,glm::value_ptr(matrix));
    return true;
}

bool Shader::setUniformVector2f(const char* uniform,vec2 vec,GLboolean useShader )
{
    if (uniform == NULL) {
        cerr << "uniform is NULL" << endl;
        return false;
    }
    if (useShader) {
        use();
    }
    glUniform2fv(glGetUniformLocation(programID,uniform),1,value_ptr(vec));
    return true;
}

bool Shader::setUniformVector3f(const char* uniform,vec3 vec,GLboolean useShader)
{
    if (uniform == NULL) {
        cerr << "uniform is NULL" << endl;
        return false;
    }
    if (useShader) {
        use();
    }
    glUniform3fv(glGetUniformLocation(programID,uniform),1,value_ptr(vec));
    return true;
}

bool Shader::setUniformVector4f(const char* uniform,vec4 vec,GLboolean useShader )
{
    if (uniform == NULL) {
        cerr << "uniform is NULL" << endl;
        return false;
    }
    if (useShader) {
        use();
    }
    glUniform4fv(glGetUniformLocation(programID,uniform),1,value_ptr(vec));
    return true;
}

bool Shader::setUniform1f(const char *uniform,GLfloat value,GLboolean useShader)
{
    if (uniform == NULL) {
        cerr << "uniform is NULL" << endl;
        return false;
    }
    if (useShader) {
        use();
    }
    glUniform1f(glGetUniformLocation(programID,uniform),value);
    return true;
}

bool Shader::setUniform1i(const char *uniform,GLint value,GLboolean useShader)
{
    if (uniform == NULL) {
        cerr << "uniform is NULL" << endl;
        return false;
    }
    if (useShader) {
        use();
    }
    glUniform1i(glGetUniformLocation(programID,uniform),value);
    return true;
}

bool Shader::setUniformSample2D(const char* uniform,GLint layout,GLboolean useShader)
{
    if (uniform == NULL) {
        cerr << "uniform is NULL" << endl;
        return false;
    }
    if (useShader) {
        use();
    }
    glUniform1i(glGetUniformLocation(programID,uniform),layout);
    return true;
}
