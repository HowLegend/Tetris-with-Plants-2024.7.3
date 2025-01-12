#pragma once
#include "Block.h"
#include "AdvanceBlock.h"

class GameBlock : public Block
{
public:
    // 构造函数
    GameBlock();
    // 含参构造函数  根据参数给的行列信息进行初始化  用于读取存档的方块  数组格式“类型 + 8个位置坐标参数”
    GameBlock(int* blockInfo);
    // 拷贝构造函数 用来拷贝预告方块的性质
    GameBlock(Block* other);
    // 析构函数
    ~GameBlock();
    // 重载=
    GameBlock& operator=(const GameBlock& other);

    // 画出方块,给定游戏边界
    void draw(int leftMargin, int topMargin);
    // 对外的一个接口 用于获得方块类型
    int getBlockType();

private:
    IMAGE* img; // 用一个指针指向同一张图片（subBlock）,标识该方块类型对应的图片
};
