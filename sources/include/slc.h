/**
 * @Author  JingleCath
 * @Date  4/1/23 - 9:33 PM
 * @Version 0.1
 * @Description .
*/


#ifndef BASETEST_SLC_H
#define BASETEST_SLC_H

#include <iostream>

#define STR_MAX_SIZE 51

typedef struct{
    char data[STR_MAX_SIZE];            // 默认50，舍弃data[0]
    int length;                         // 字符串长度
}str;

// 初始化字符串
void initStr(str &s){
    s.length = 0;
}
// Initialize str
void initStr(str &s, const std::string& str){
    s.length = 0;
    for(int i = 1; i < STR_MAX_SIZE && i <= str.size(); i++){
        s.data[i] = str[i - 1];
        s.length++;
    }
}

// print str
void printStr(str s, std::string name){
    std::cout << name << ": ";
    for(int i = 1; i <= s.length; i++)
        std::cout << s.data[i];
    std::cout << std::endl;
}

// 获取串长
int getLen(str &s){
    return s.length;
}

// get next 数组
int* getNextArray(str s){
    // create a next array with length of s.length + 1 . dump first one
    int *next = new int[s.length + 1];
    next[1] = 0;
    for(int ptr = 2; ptr <=s.length; ptr++)
        next[ptr] = 1;
    int ptr1 = 1, ptr2 = 2;
    int len = 1;
    for(;len < s.length - 2; len++,ptr1++){
        for(;ptr2 <= s.length - 1; ptr2++){
            if(s.data[ptr2] == s.data[ptr1] && next[ptr2] == len)
                next[ptr2 + 1] = len + 1;
        }
        ptr2 = len + 1;
    }

    return next;
}

/**
 * KMP 算法
 * @param mainStr 主串
 * @param tempStr 模式串
 * @param next 模式串的匹配失败时的next数组
 * @return
 * - 正数为匹配位置
 * - -1为匹配失败
 */
int KMPAlgorithm(str mainStr, str tempStr, const int next[]){
    int times = 0;                  // 比较次数
    int i = 1, j = 1;               // 定义主串和模式串的指针
    int m = getLen(mainStr), n = getLen(tempStr);       // 获取串长
    while (i <= m && j <= n){       // 合法判断
        if(mainStr.data[i] == tempStr.data[j]){
            i++;    j++;            // 主串、模式串指针后移

        }
        else
            j = next[j];            // 主串指针不变，模式串指针后移到失配对应next数组指定位置
    }
    std::cout << "Comparing times: " << times << std::endl;
    if(j > n)                       // 匹配成功
        return i - n;               // 返回匹配的头位置
    else                            // 匹配成功
        return -1;
}

/**
 * TODO 朴素的暴力匹配算法
 * @param mainStr 主串
 * @param tempStr 模式串
 * @return
 * - 正数为匹配位置
 * - -1为匹配失败
 */
int simpleMatch(str mainStr, str tempStr){
    return 0;
}

#endif /* BASETEST_SLC_H */
