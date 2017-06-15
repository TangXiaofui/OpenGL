//
//  config.hpp
//  Game
//
//  Created by txh on 2017/6/4.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef config_hpp
#define config_hpp

#include <string>
#include <map>
#include <list>
#include <glm/glm.hpp>
using namespace std;
using namespace glm;

struct GameConfig{
    
    /**
     读取ini配置文件

     @param fileName 配置文件路径
     @return >= 0 代表成功
     */
    int parse(string fileName);
    
    
    /**
     根据section和key获取相对应的value

     @param section ini文件中section的名称
     @param key ini文件中key的名称
     @param defaultValue 当ini文件中不存在相应value时，返回的默认参数
     @return 返回值
     */
    string get(string section, string key, string defaultValue);
    bool getBool(string section, string key, bool defaultValue);
    int getInteger(string section, string key, int defaultValue);
    double getReal(string section, string key, double defaultValue);

    vec2 getVec2(string section, string key, vec2 defaultValue);
    vec3 getVec3(string section, string key, vec3 defaultValue);
    
    list<string> getStrings(string section, string key);

private:
    map<string,list<string>> values;
    string fileName;
};

#endif /* config_hpp */
