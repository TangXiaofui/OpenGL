//
//  Utility.cpp
//  Game
//
//  Created by txh on 2017/6/3.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "Utility.hpp"

namespace Util{
    //相关资源的路径
#define RESOURCE_PATH "/Users/zj-db0860/LearnOpenGL/6.cubeMaps"
    
    void processFilePath(string &filepath)
    {
        if (filepath.size() == 0) {
            cerr << "filepath is NULL" << endl;
            return ;
        }
        if (filepath[0] == '/') {
            return ;
        }
        else if(filepath[0] == '.'){
            filepath = filepath.erase(0,1);
            filepath = RESOURCE_PATH + filepath;
            return ;
        }
        else
        {
            filepath = "/" + filepath;
            filepath = RESOURCE_PATH + filepath;
            return ;
        }
    }
    
    
    
    unique_ptr<GLfloat,ArrayDeletor> getVertexs(GLfloat width,GLfloat height)
    {
        return unique_ptr<GLfloat,Util::ArrayDeletor>(new GLfloat[30]{
            //cood                    //tex
            -width, height, 0.0f,        0.0f,1.0f,
            -width,-height, 0.0f,        0.0f,0.0f,
             width,-height, 0.0f,        1.0f,0.0f,
             width,-height, 0.0f,        1.0f,0.0f,
             width, height, 0.0f,        1.0f,1.0f,
            -width, height, 0.0f,        0.0f,1.0f
        });
    }
    
    
    //窗口边界
    const vec2 WINDOW_BORDER = vec2(1000,1000);
    
    //正交投影
    const mat4 PROJECTION = glm::ortho(-500.0f, 500.0f, -500.0f, 500.0f, -1.0f, 1.0f);
    
    //按键位置映射
    const mat3 TRANS = mat3(1.0f,          0.0f, -500.0f,
                            0.0f,-500.0f/390.0f,  500.0f,
                            0.0f,          0.0f,   0.0f);
    //重力加速度
    float GRAVITY = 1000.0f;
    
    //当点击空格键时，设置bird的垂直速度
    float BIRD_VERTICAL_VELOCITY = 400.0f;
    //bird水平移动速度
    float BIRD_HORIZON_VELOCITY = 1.0f;
    
    //tube移动速度
    float TUBE_SPEED = 200.0f;
    
    //particle速度参数
    float PARTICLE_SPEED = 5.0f;
}
