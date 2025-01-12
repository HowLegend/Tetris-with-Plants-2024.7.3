#include "Block_S.h"

Block_S::Block_S()
{
    // 设定类型编号
    blockType = 2;

    // 当前新建的俄罗斯方块的img指针指向它这个方块种类的subBlock
    img = imgs[blockType - 1];

    // 该方块的形状信息
    typeInfo[0] = 2;
    typeInfo[1] = 4;
    typeInfo[2] = 5;
    typeInfo[3] = 7;

    // 初始化四个 subBlocks 位置
    for (int i = 0; i < 4; i++)
    {
        int num = typeInfo[i];
        subBlocks[i].row = num / 2 - 3; // 在地图外缓慢掉入游戏区域
        subBlocks[i].col = num % 2 + 4; // 居中
    }
}

Block_S::~Block_S()
{
}
