#pragma once
#include "Block.h"

class AdvanceBlock : public Block
{
public:
    // 构造函数
    AdvanceBlock();
    // 析构函数
    ~AdvanceBlock();

    // 画出方块,给定游戏边界
    void draw(int leftMargin, int topMargin);
    // 对外的一个接口 用于获得方块类型
    int getBlockType();

protected:
    IMAGE* img; // 每种类型中的小方块是相同的，所以用一个指针指向同一张图片（subBlock）就可以了
};
