#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include "Button.h"
#include "Game.h"
#include <conio.h>
#include <mmsystem.h>
#include <Windows.h>
#include <cstdio>

using namespace std;

// 页面内系统类
class InterfaceBook
{
public:
    // 构造函数
    InterfaceBook(int width, int height);
    // 析构函数
    ~InterfaceBook();
    // 初始化系统逻辑体系，创建图形窗口，设置页面和按钮
    void init();
    // 运行，进入消息循环
    void run();

private:
    // 添加一个页面
    void addPage(IMAGE* page);
    // 在指定页面上添加一个按钮
    void addButton(int index, Button* button);
    // 鼠标点击
    void mouseClick(int mouseX, int mouseY);
    // 鼠标移动到按钮上方
    void mouseMove(int mouseX, int mouseY);
    // 绘制当前页面的内容
    void draw();
    // 设置当前显示的页面是哪一页
    void setCurrentIndex(int index);
    // 提供第i页第j个按钮的接口
    Button* getButton(int i, int j);

    // 获取player的存档lastMap,返回值表示该player是否有存档
    bool getLastInfo(char mode);
    // 画出存档lastMap的图像、预告方块和游戏方块
    void drawLastMap_NextBlock_CurBlock();
    // 画出存档中的分数和按键信息
    void drawLastScoreAndKeyInfo();
    // 更新玩家更换游戏界面的预览背景和棋盘大小
    void updateBackground(char mode, string bg);

private:
    int width;                              // 宽度
    int height;                             // 高度
    int currentIndex;                       // 当前页面索引代号
    vector<IMAGE*> pages;                   // 存储所有页面的图片指针
    vector<vector<Button*>> page_buttons;   // 存储每个页面上的按钮
    bool exit;                              // 退出程序的Flag

    bool notNeedWait;   // 一般按钮不需要程序停滞，但有的按钮不用刷新页面，需要程序停滞几秒
    string recordIndex; // 存档编号
    bool hasRecord;     // 表示该玩家有存档

    char player[15];             // 玩家名称
    int lastScore;               // 玩家存档分数score
    vector<vector<int>> lastMap; // 玩家存档map
    int lastNextBlockInfo[9];    // 玩家存档中的预告方块 类型编号+8个位置参数
    int lastCurBlockInfo[9];     // 玩家存档的游戏方块 类型编号+8个位置参数

    // 玩家对模式的设置
    char mode;      // 游戏棋盘大小，分为A和B
    int speed;      // 游戏速度
    bool plantMode; // 植物 游戏玩法

    // 玩家对按键的设置
    bool useDirectionKeys;  // 是否使用方向键预设
    char keyArray_ASCII[8]; // 0~3存储玩家自定义的上下左右按键，4、5存储了“暂停菜单”、“瞬间下落”的按键, 6、7存储“寒冰”、“炸弹”

    // 玩家对背景的选择
    string bg;
    // 玩家对方块样式的选择
    string bk;
    // 玩家对游戏音乐的选择
    string music;
};
