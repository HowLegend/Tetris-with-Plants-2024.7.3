#include "GameBlock.h"

GameBlock::GameBlock()
{
    // 当前新建的俄罗斯方块的img指针指向它这个方块种类的subBlock
    img = imgs[blockType - 1];
}

GameBlock::GameBlock(int* blockInfo)
{
    blockType = blockInfo[0];
    // 当前新建的俄罗斯方块的img指针指向它这个方块种类的subBlock
    img = imgs[blockType - 1];
    // 拷贝存档中四个 subBlocks 位置
    for (int i = 0; i < 4; i++)
    {
        subBlocks[i].row = blockInfo[2 * i + 1]; // 在地图外缓慢掉入游戏区域
        subBlocks[i].col = blockInfo[2 * i + 2]; // 居中
    }
}

GameBlock::GameBlock(Block* other)
{
    int otherBlockType = other->getBlockType();

    blockType = otherBlockType;     // 拷贝类型
    img = imgs[otherBlockType - 1]; // 拷贝图像

    // 复制四个 subBlocks 位置
    Point* otherSubBlocks = other->getSubBlockLocationArray();
    for (int i = 0; i < 4; i++)
    {
        subBlocks[i] = otherSubBlocks[i];

        // int num = blocks[otherBlockType - 1][i];
        // subBlocks[i].row = num / 2 - 3; // 在地图外缓慢掉入游戏区域
        // subBlocks[i].col = num % 2 + 4; // 居中
    }
}

GameBlock::~GameBlock()
{
    delete img;
    img = NULL;
}

GameBlock& GameBlock::operator=(const GameBlock& other)
{
    if (this == &other) // 通过判断地址是否相同，来防止自己复制自己
    {
        return *this;
    }
    else
    {
        this->blockType = other.blockType;
        for (int i = 0; i < 4; i++)
        {
            this->subBlocks[i] = other.subBlocks[i];
        }
        this->img = other.img; // 不需要new一个，都是指向同源的图片素材
        return *this;
    }
}

void GameBlock::draw(int leftMargin, int topMargin)
{
    for (int i = 0; i < 4; i++)
    {
        if (subBlocks[i].row >= 0)
        {
            int x = leftMargin + subBlocks[i].col * subBlockSize; // 算出x坐标
            int y = topMargin + subBlocks[i].row * subBlockSize;  // 算出y坐标
            putimage(x, y, img);                                  // 在（x，y）出画出图像
        }
    }
}

int GameBlock::getBlockType()
{
    return blockType;
}
