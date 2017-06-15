//
//  Font2D.cpp
//  Game
//
//  Created by txh on 2017/5/26.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Font2D.hpp"
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;


Font2D::Font2D()
:shader(nullptr),
texture(nullptr)
{
    
}

Font2D::Font2D(shared_ptr<Shader> shader,shared_ptr<Texture> texture)
:Font2D()
{
    this->shader = shader;
    this->texture = texture;
}

Font2D::~Font2D()
{

}


void Font2D::load(shared_ptr<Shader> shader,shared_ptr<Texture> texture)
{
    this->shader = shader;
    this->texture = texture;
}

GLint Font2D::printText2D(const char * text, int x, int y, int size,string uniformSampler)
{
    if (text == NULL) {
        cerr << "ERROR::text is nullptr" << endl;
        return -1;
    }
    
    if (shader == nullptr || texture == nullptr) {
        cerr << "ERROR::shader or texture is nullptr" << endl;
        return -1;
    }
    
    unsigned int length = strlen(text);
    
    //根据字体位置以及大小获取顶点
    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> UVs;
    for ( unsigned int i=0 ; i<length ; i++ ){
        
        glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
        glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
        glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
        glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );
        
        char character = text[i];
        float uv_x = (character%16)/16.0f;
        float uv_y = (character/16)/16.0f;
        
        glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
        glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
        glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
        glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
        
        vertices.push_back(vertex_up_left   );
        vertices.push_back(uv_up_left   );
        
        vertices.push_back(vertex_down_left );
        vertices.push_back(uv_down_left );
        
        vertices.push_back(vertex_up_right  );
        vertices.push_back(uv_up_right  );
        
        vertices.push_back(vertex_down_right);
        vertices.push_back(uv_down_right);
        
        vertices.push_back(vertex_up_right);
        vertices.push_back(uv_up_right);
        
        vertices.push_back(vertex_down_left);
        vertices.push_back(uv_down_left);
    }
    
    //设置缓存
    
    VAO.setBuffer(&vertices[0], vertices.size() * sizeof(glm::vec2));
    VAO.setBufferAttrib(0, 2, 2 * sizeof(vec2), (void*)0 );
    VAO.setBufferAttrib(1, 2, 2 * sizeof(vec2), (void*)(sizeof(vec2)));
    
    shader->use();
    texture->use();
    shader->setUniformSample2D(uniformSampler.c_str(), 0);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
    VAO.unbind();
    glDisable(GL_BLEND);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    return 0;
}


