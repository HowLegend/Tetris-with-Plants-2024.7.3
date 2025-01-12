#pragma once
#include "Block.h"
#include "GameBlock.h"

class BlockShadow : public Block
{
public:
    // 构造函数
    BlockShadow();
    // 有参构造函数 传入影子的body，一步到位
    BlockShadow(Block* body);
    // 析构函数
    ~BlockShadow();

    // 重载=
    BlockShadow& operator=(const BlockShadow& other);

    // 成为body方块的影子shadow
    void beShadowOf(Block* body);
    // 画出方块,给定游戏边界
    void draw(int leftMargin, int topMargin);
    // 对外的一个接口 用于获得方块类型
    int getBlockType();
    // 加载入ShadowImg的图片，用静态函数加载静态变量，因为后来扩展“读档功能”时发现还未创建block就需要让外部调用图像
    void lodShadowImg();

private:
    IMAGE* img; // 每种类型中的小方块是相同的，所以用一个指针指向同一张图片（subBlock）就可以了
};
