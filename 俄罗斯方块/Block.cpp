#include "Block.h"

// 静态成员函数初始化
IMAGE* Block::imgs[7] = {
    NULL,
};
int Block::subBlockSize = 27;

Block::Block()
{
    // 初始化blockType
    blockType = 0;

    // 初始化subBlocks
    for (int i = 0; i < 4; i++)
    {
        subBlocks[i].row = 0;
        subBlocks[i].col = 0;
    }
}

Block::~Block()
{
}

void Block::loadSubBlockImg(string bk)
{
    // 给 imgs[0]-imgs[6] 的七个指针进行赋值,subBlock
    // 载入 subBlock 图片
    IMAGE tempImg;
    if (bk == "bk1")
    {
        loadimage(&tempImg, "./materials/subBlock_1.png", 216, 27);
    }
    else if (bk == "bk2")
    {
        loadimage(&tempImg, "./materials/subBlock_2.png", 216, 27);
    }
    // 截取图片
    SetWorkingImage(&tempImg); // 设置操作对象
    for (int i = 0; i < 7; i++)
    {
        imgs[i] = new IMAGE;
        getimage(imgs[i], i * subBlockSize, 0, subBlockSize, subBlockSize);
    }
    SetWorkingImage(); // 恢复默认工作区
}

void Block::drop()
{
    for (Point& sBlock : subBlocks) // 引用传值
    {
        sBlock.row++;
    }
}

void Block::moveLeft()
{
    for (int i = 0; i < 4; i++)
    {
        subBlocks[i].col--;
    }
}

void Block::moveRight()
{
    for (int i = 0; i < 4; i++)
    {
        subBlocks[i].col++;
    }
}

void Block::rotate()
{
    // 直接套用数学公式结论，实现逻辑上的旋转
    Point centerPoint = subBlocks[1]; // 旋转中心
    for (Point& rotatePoint : subBlocks)
    {
        Point oldRotatePoint = rotatePoint;
        rotatePoint.col = centerPoint.col - oldRotatePoint.row + centerPoint.row;
        rotatePoint.row = centerPoint.row + oldRotatePoint.col - centerPoint.col;
    }
}

bool Block::isInMapLegally(const vector<vector<int>>& map) const
{
    // 获取map的边界rows和cols
    int rows = map.size();
    int cols = map[0].size();
    // 判断
    for (int i = 0; i < 4; i++)
    {
        if (subBlocks[i].row < 0) // 刚生成的方块，部分subBlock还没下落
            continue;
        if (subBlocks[i].row < 0 || subBlocks[i].row >= rows ||                                             // 检验 行
            subBlocks[i].col < 0 || subBlocks[i].col >= cols ||                                             // 检验 列
            (map[subBlocks[i].row][subBlocks[i].col] != 0 && map[subBlocks[i].row][subBlocks[i].col] != 8)) // 检验 与其他方块有没有重叠
        {
            return false;
        }
    }
    return true;
}

void Block::solidify(vector<vector<int>>& map) const
{
    // 将方块自身的类型数字写入map
    for (int i = 0; i < 4; i++)
    {
        if (subBlocks[i].row < 0)
            continue;
        map[subBlocks[i].row][subBlocks[i].col] = blockType;
    }
}

Point* Block::getSubBlockLocationArray()
{
    return subBlocks;
}

IMAGE** Block::getSubBlockImages()
{
    return imgs;
}
