//
//  config.cpp
//  Game
//
//  Created by txh on 2017/6/4.
//  Copyright © 2017年 txh. All rights reserved.
//

#include "config.hpp"
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <memory>
#include <string.h>


/**
 局部函数，用于组成map的key值

 @param section ini文件中的section
 @param key ini文件中的key
 @return map中的key值，用于索引
 */
static string makeKey(string section, string key)
{
    string index = section + key;
    transform(index.begin(), index.end(), index.begin(), ::tolower);
    return index;
}

string GameConfig::get(string section, string key, string defaultValue)
{
    string index = makeKey(section, key);
    auto p = values.find(index);
    return p != values.end() ? p->second.back() : defaultValue;
}

list<string> GameConfig::getStrings(string section, string key)
{
    string index = makeKey(section, key);
    auto p = values.find(index);
    return p != values.end() ? p->second : list<string>() ;
}

bool GameConfig::getBool(string section, string key, bool defaultValue)
{
    string value = get(section, key, "");
    transform(value.begin(), value.end(), value.begin(), ::tolower);
    if (value == "true" || value == "yes" || value == "on" || value == "1") {
        return true;
    }
    else if(value == "false" || value == "no" || value == "off" || value == "0"){
        return false;
    }
    else
        return defaultValue;
    
}
int GameConfig::getInteger(string section, string key, int defaultValue)
{
    string value = get(section, key, "");
    const char *begValue = value.c_str();
    char *endValue;
    long intValue = strtol(begValue, &endValue, 0);
    
    return endValue > begValue ? static_cast<int>(intValue) : defaultValue;
}

double GameConfig::getReal(string section, string key, double defaultValue)
{
    string value = get(section, key, "");
    const char *begValue = value.c_str();
    char *endValue;
    double dValue = strtod(begValue, &endValue);
    return endValue > begValue ? dValue : defaultValue;
}


vec2 GameConfig::getVec2(string section, string key, vec2 defaultValue)
{
    string value = get(section, key, "");
    char *vec;
    float f[2];
    int i;
    char *endValue;
    for (vec = strtok((char*)value.c_str(), ","),i = 0 ; vec && i < 2; vec = strtok(NULL, ",")) {
        f[i++] = static_cast<float>(strtod(vec, &endValue));
        if (endValue == vec) {
            return defaultValue;
        }
    }
    return vec2(f[0],f[1]);
}
vec3 GameConfig::getVec3(string section, string key, vec3 defaultValue)
{
    string value = get(section, key, "");
    char *vec;
    float f[3];
    int i;
    char *endValue;
    for (vec = strtok((char*)value.c_str(), (char*)","),i = 0 ; vec && i < 3; vec = strtok(NULL, ",")) {
        f[i++] = static_cast<float>(strtod(vec, &endValue));
        if (endValue == vec) {
            return defaultValue;
        }
    }
    return vec3(f[0],f[1],f[2]);
}

/**
 匿名空间，该类只能用在本文件。
 该类主要用于处理单行字符串
 
 */
namespace {
    class LineProcess{
    public:
        /**
         构造函数

         @param ln 单行字符串
         */
        LineProcess(char *ln):str(ln),err(0){};
        
        
        
        /**
         跳过字符串前面的空格

         @return 返回自身的引用
         */
        LineProcess& skipSpace()
        {
            while (!err && *str && isspace(*str)) {
                ++str;
            }
            return *this;
        }
        
        /**
         删除字符串后面的空格

         @param s 字符串的起始指针
         @param e 字符串的末尾指针
         @return 删除尾部空格的字符串
         */
        string rstrip(char *s,char *e)
        {
            while (e > s && isspace(e[-1])) {
                --e;
            }
            return string(s,e);
        }
        
        
        /**
         读取字符串第一个非空格的字符

         @return 字符串第一个非空格的字符
         */
        char peekChar()
        {
            skipSpace();
            return *str;
        }
    
        
        /**
         判断字符串第一个非空格的字符是否是某个字符，并设置相应错误状态

         @param c 用于匹配的字符
         @return 返回自身的引用
         */
        LineProcess& match(char c){
            skipSpace();
            err = (*str != c);
            return *this;
        }
        
        
        /**
         跳过s个字符，并返回自身的引用

         @param s 跳过字符的个数
         @return 返回自身的引用
         */
        LineProcess& skip(size_t s){
            str += s;
            return *this;
        }
        
        
        /**
         读取到截止字符c字符之间的字符串

         @param c 截止字符c
         @return 截取到的字符串，已经经过尾部空格处理
         */
        string comsumeTill(char c)
        {
            skipSpace();
            char *end = str;
            while (!err && *end && *end != c) {
                ++end;
            }
            if (*end != c) {
                err = -1;
                return "";
            }
            
            char *s = str;
            str = end;
            return rstrip(s, end);
        }
        
        /**
         读取到终止／换行／注释等字符之间的字符串
         
         @return 截取到的字符串，已经经过尾部空格处理
         */
        string comsumeTillEnd()
        {
            skipSpace();
            char *end = str;
            while (!err && *end && *end != ';' && *end != '#' && !isspace(*end)) {
                ++end;
            }
            char *s = str;
            str = end;
            return rstrip(s, end);
        }

        char *str;
        int err;
    };
}


int GameConfig::parse(string fileName)
{
    if(fileName.size() == 0)
        return -1;
    this->fileName = fileName;
    FILE *fp = fopen(fileName.c_str(), "r");
    unique_ptr<FILE,decltype(fclose)*> release(fp,fclose);
    static const int BUFFSIZE = 1024;
    char *buf = new char[BUFFSIZE];
    unique_ptr<char[]> release1(buf);
    int lineNo = 0;
    
    string section,key;
    int err = 0;
    while (!err && fgets(buf, BUFFSIZE, fp)) {
        ++lineNo;
        //读取一行,传递给字符串处理类
        LineProcess lp(buf);
        char c = lp.peekChar();
        //判断当前字符是否是注释符，或行结束符，是的话则continue
        if (c == ';' || c == '#' || c == '\0') {
            continue;
        }
        //说明是一个section行
        else if(c == '['){
            section = lp.skip(1).comsumeTill(']');
            err = lp.match(']').err;
            key = "";
        }
        //如果开头是空格，说明是当前key的下一个value
        else if( isspace(buf[0]) ){
            if ( !section.empty() && !key.empty()) {
                values[makeKey(section, key)].push_back(lp.comsumeTill('\0'));
            }
            else
            {
                err = -1;
            }
        }
        //否则先读取key，然后在读取value，并插入map缓存
        else{
            LineProcess lpc = lp;
            key = lp.comsumeTill('=');
            if (lp.peekChar() == '=') {
                lp.skip(1);
            }
            else{
                lp = lpc;
                key = lp.comsumeTill(':');
                err = lp.match(':').err;
                if (!err) {
                    lp.skip(1);
                }
            }
            string value = lp.comsumeTillEnd();
            values[makeKey(section, key)].push_back(value);
        }
    }
    
    return err == 0? lineNo : err;
}
