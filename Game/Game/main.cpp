//
//  main.cpp
//  Game
//
//  Created by txh on 2017/5/24.
//  Copyright © 2017年 txh. All rights reserved.
//
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Physic.hpp"
#include "Windows.hpp"
#include "Object.hpp"
#include <memory>
#include "Tube.hpp"
#include <vector>
#include <random>
#include <memory>
#include "Button.hpp"
#include "Font2D.hpp"
#include "Particle.hpp"
#include "ResourceManager.hpp"
#include "Bird.hpp"
#include "config.hpp"

using namespace std;
using namespace glm;

//水管个数(上下水管表示一个)
#define NUM 99

//bird 缩放大小
#define BIRD_SCALE 25

//窗口名称
static string WINDOW_NAME = "Game";
//窗口背景
static vec3 WINDOW_BACK_COLOR = vec3(0.0f);

//按键框大小
static const vec2 START_BUTTON_BORDER = vec2(104.0f,58.0f);
static const vec2 OVER_BUTTON_BORDER = vec2(80.0f,28.0f);

//按键框位置
static const vec3 START_BUTTON_POSITION = vec3(0.0f);
static const vec3 OVER_BUTTON_POSITION = vec3(0.0f);

//游戏结束语
static const char* GAME_OVER_LABEL = "Game Over";
//结束语位置
static const vec2 GAME_OVER_LABEL_POSITION = vec2(175,350);
//字体大小
static const int GAMEOVER_FONT_SIZE = 50;

//计数位置
static const vec2 COUNT_LABEL_POSITION = vec2(350,500);
//字体大小
static const int COUNT_FONT_SIZE = 30;

//tube长度／宽度
static const vec2 TUBE_BORDER = vec2(80,800);

//tube的间隔
static GLfloat TUBE_HORIZON_GAP = 500.0f;
//竖直两个tube的间隔
static GLfloat TUBE_VERTICAL_GAP = 150.0f;
//竖直方向tube偏移
static GLfloat TUBE_VERTICAL_OFFSET = 80.0f;


unique_ptr<Bird> bird;
unique_ptr<Button> button;
unique_ptr<Button> gameoverButton;
unique_ptr<ParticleGenerator> particlegenerator;
unique_ptr<Font2D> font;
unique_ptr<GameConfig> gameConfig;

vector<shared_ptr<Tube>> tubes;
bool isStart;
bool isLose;
void init();
void readConfig(string configName);
int passTubes;
bool isPass[NUM];


//全局配置，防止全局污染，命名空间,头文件中不需要的移到cpp


void keyCallback(GLFWwindow *window,int key,int scancode,int action,int mode);
void mouseButtonCallback(GLFWwindow*,int,int,int);

int main(int argc, const char * argv[]) {
    
    //读取配置文件，初始化全局变量
    readConfig("/Users/zj-db0860/LearnOpenGL/Game/Config/gameConfig.ini");
    
    //窗口初始化
    Window win(4,Util::WINDOW_BORDER.x,Util::WINDOW_BORDER.y,WINDOW_NAME.c_str());
    win.init();
    win.setKeyCallback(keyCallback);
    win.setMouseCallback(mouseButtonCallback);
    win.setBackgroundColor(WINDOW_BACK_COLOR);
    
    //环境初始化
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        cout << "glew initial failed." << endl;
        return -1;
    }
    glGetError();
    
    
    //初始化各个组件
    init();
    
    //用于保存上一帧时间，用于计算帧率
    GLfloat lastTime = glfwGetTime();

    //用于写游戏逻辑
    win.draw([&]{
        
        GLfloat curTime = glfwGetTime();
        GLfloat deltaTime = curTime - lastTime;
        lastTime = curTime;
        
        //游戏还未开始，只显示按钮
        if(!isStart)
        {
           button->draw();
        }
        else{
            //当Game Over时，停止刷新位置，保存结束时状态
            if (!isLose) {
                bird->move(deltaTime);
                particlegenerator->update(deltaTime, 2, *bird,vec2(-bird->getRadius()));
            }
            
           
            bird->draw();
            particlegenerator->draw();
            
            for (int i = 0; i < NUM; ++i) {
                //超出屏幕就不画
                if (tubes[i]->getPosition().x < -Util::WINDOW_BORDER.x) {
                    continue;
                }
                //当靠近bird的时候才开始检测
                if (tubes[i]->getPosition().x - bird->getposition().x < Util::WINDOW_BORDER.x/4) {
                    if (bird->detectCollision(*tubes[i])) {
                        isLose = true;
                    }
                    
                }
                if (!isLose) {
                    tubes[i]->move(deltaTime);
                }
                tubes[i]->draw();
                
                if (tubes[i]->getPosition().x+tubes[i]->getBound().x < bird->getposition().x) {
                    if (!isPass[i]) {
                        isPass[i] = true;
                        ++passTubes;
                    }
                }
            }
            char buf[5] = {0};
            snprintf(buf, sizeof(buf),"%d",passTubes);
            font->printText2D(buf, COUNT_LABEL_POSITION.x,COUNT_LABEL_POSITION.y , COUNT_FONT_SIZE,"texture0");
            
            //游戏失败时，出现按键和标语
            if (isLose) {
                gameoverButton->draw();
                font->printText2D(GAME_OVER_LABEL, GAME_OVER_LABEL_POSITION.x, GAME_OVER_LABEL_POSITION.y, GAMEOVER_FONT_SIZE,"texture0");
            }
        
        }
    });
    
    win.loop();
    ResourceManeger::clear();
    return 0;
}


void init()
{
    isStart = false;
    isLose = false;
    passTubes = 0;
    memset(isPass, 0, NUM*sizeof(bool));
    
    //着色器命名与脚本一致方便去重
    shared_ptr<Shader> commonShader = ResourceManeger::loadShader("Script/common.vertex","Script/common.fragment","common");
    shared_ptr<Shader> particleShader = ResourceManeger::loadShader("Script/particle.vertex","Script/particle.fragment","particle");
    shared_ptr<Shader> text2DShader = ResourceManeger::loadShader("Script/text2D.vertex", "Script/text2D.fragment", "text2D");
    
    //纹理命名与资源名称一致方便去重
    shared_ptr<Texture> startButtonTexture = ResourceManeger::loadTexture("texture/startButton.png", "startButton",true);
    shared_ptr<Texture> okButtonTexture = ResourceManeger::loadTexture("texture/OKButton.png", "OKButton",true);
    shared_ptr<Texture> birdTexture = ResourceManeger::loadTexture("texture/birdNormal.png", "birdNormal",true);
    shared_ptr<Texture> tubeTexture = ResourceManeger::loadTexture("texture/tube.png", "Tube",true);
    
    //字体设置
    shared_ptr<Texture> fontTexture = ResourceManeger::loadFont2D("Font/Holstein.DDS", "Holstein");
  
    //bird初始化
    bird.reset(new Bird(vec2( GLfloat(BIRD_SCALE - Util::WINDOW_BORDER.x/2), 0.0f ),
                        vec2(BIRD_SCALE*1.0f,BIRD_SCALE*1.0f)));
    bird->load(commonShader,birdTexture);
    
    
    //启动按键初始化
    button.reset(new Button(START_BUTTON_POSITION,START_BUTTON_BORDER));
    button->load(commonShader,startButtonTexture);
    
    
    //GameOver按键初始化
    gameoverButton.reset(new Button(OVER_BUTTON_POSITION,OVER_BUTTON_BORDER));
    gameoverButton->load(commonShader,okButtonTexture);
    
    //粒子系统初始化
    particlegenerator.reset(new ParticleGenerator(500));
    particlegenerator->load(particleShader,birdTexture);

    
    
    //初始化管道
    default_random_engine e;
    tubes.clear();
    for (int i = 0; i < NUM; ++i) {
        tubes.push_back(make_shared<Tube>(vec3(Util::WINDOW_BORDER.x/2 + TUBE_HORIZON_GAP * i, static_cast<GLint>( e() % 8 - 4) * TUBE_VERTICAL_OFFSET, 0.0f),
                                          TUBE_BORDER,
                                          TUBE_VERTICAL_GAP));
        tubes[i]->load(commonShader,tubeTexture);
    }
    
    //初始化字体
    font.reset(new Font2D);
    font->load(text2DShader, fontTexture);
}

void readConfig(string configName)
{
    gameConfig.reset(new GameConfig);
    //读取配置文件
    gameConfig->parse(configName);
    
    //读取配置信息
    WINDOW_NAME = gameConfig->get("window", "name", "window");
    WINDOW_BACK_COLOR = gameConfig->getVec3("window", "backcolor", vec3(1.0f));
    
    TUBE_HORIZON_GAP = gameConfig->getReal("tube", "horizon_gap", 500.0f);
    TUBE_VERTICAL_GAP = gameConfig->getReal("tube", "verticle_gap", 150.0f);
    TUBE_VERTICAL_OFFSET = gameConfig->getReal("tube", "verticle_offset", 80.0f);
    
    
    Util::GRAVITY = gameConfig->getReal("bird", "gravity", 1000.0f);
    Util::BIRD_VERTICAL_VELOCITY = gameConfig->getReal("bird", "verticle_velo", 400.0f);
    Util::BIRD_HORIZON_VELOCITY = gameConfig->getReal("bird", "horizen_velo", 1.0f);
    
    Util::TUBE_SPEED = gameConfig->getReal("tube", "speed", 200.0f);
    
    Util::PARTICLE_SPEED = gameConfig->getReal("particle", "speed", 5.0f);
    
}


void keyCallback(GLFWwindow *window,int key,int scancode,int action,int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    //点击空格键给bird的y轴一个速度
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        vec2 velo = vec2(0.0f,Util::BIRD_VERTICAL_VELOCITY);
        bird->setVelocity(velo);
    }

}

//刚开始没有按键检测
void mouseButtonCallback(GLFWwindow *windows,int key,int action,int mode)
{
    if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos,ypos;
        glfwGetCursorPos(windows,&xpos, &ypos);
        //坐标转换，将鼠标坐标转换成屏幕坐标
        vec3 trans_after = vec3(xpos,ypos,1.0f) * Util::TRANS ;
        //当游戏还没开始 才进行按键检测
        if (!isStart) {
            button->detectPress(trans_after.x, trans_after.y);
        }

        //当游戏开始并且已经gameover才进行检测
        if (isStart && isLose) {
            gameoverButton->detectPress(trans_after.x, trans_after.y);
        }
    }
    if (key == GLFW_MOUSE_BUTTON_LEFT && action == 0) {
        cout << " release " << endl;
        //开始按键释放判断，设置相应状态
        if (button->getButtonState()) {
            isStart = true;
            button->setButtonUp();
        }
        //结束按键释放判断，设置相应状态
        if (gameoverButton->getButtonState()) {
            isStart = false;
            isLose = false;
            gameoverButton->setButtonUp();
            init();
        }
    }
}
