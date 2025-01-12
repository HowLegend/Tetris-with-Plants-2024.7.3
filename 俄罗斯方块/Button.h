#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 按钮
class Button
{
public:
    // 构造函数
    Button(int x, int y, int width, int height, const char* str, const function<void()>& onClick);
    // 析构函数
    ~Button();
    // 检查鼠标是否在按钮上方
    void checkMouseOver(int mouseX, int mouseY);
    // 检查鼠标点击如果在按钮内，执行仿函数
    bool checkClick(int mouseX, int mouseY);
    // 绘制按钮
    void draw();
    // 方便调用修改按钮名称，服务于按键修改后，按键直观展示
    void changeKey(char ch);
    // 更改按钮名称
    void changeName(string name);
    // 获取按钮状态 (只取第一位，只用于判断是否 时被选择按钮“*”)
    char getStatus() const;

private:
    int x;                    // 按钮左上角x坐标
    int y;                    // 按钮左上角y坐标
    int width;                // 按钮宽度
    int height;               // 按钮高度
    float scale;              // 缩放比例，用于实现鼠标悬停效果
    bool isMouseOver;         // 表示鼠标是否在按钮上方
    char text[32];            // 按钮文本
    function<void()> onClick; // 点击按钮触发的函数
};