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

// 获取串长
int getLen(str &s){
    return s.length;
}

// get next 数组
void getNextArray(str s){

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
int KMPAlgorithm(str mainStr, str tempStr, int next[]){
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

#endif /* BASETEST_SLC_H */
