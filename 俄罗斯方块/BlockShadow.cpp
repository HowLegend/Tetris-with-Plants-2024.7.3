#include "BlockShadow.h"

BlockShadow::BlockShadow()
{
    lodShadowImg();
}

BlockShadow::BlockShadow(Block* body)
{
    lodShadowImg();
    beShadowOf(body);
}

BlockShadow::~BlockShadow()
{
    delete img;
}

BlockShadow& BlockShadow::operator=(const BlockShadow& other)
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

void BlockShadow::beShadowOf(Block* body)
{
    blockType = 8;              // 类型为8（影子）
    for (int i = 0; i < 4; i++) // 复制位置
    {
        this->subBlocks[i] = body->getSubBlockLocationArray()[i];
    }
}

void BlockShadow::draw(int leftMargin, int topMargin)
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

int BlockShadow::getBlockType()
{
    return blockType;
}

void BlockShadow::lodShadowImg()
{
    IMAGE tempImg;
    // 导入“影子”图像
    // 给 imgs[7] 指针进行赋值,shadowBlock
    loadimage(&tempImg, "./materials/shadowBlock.png", 27, 27);
    // 提取图片
    SetWorkingImage(&tempImg); // 设置操作对象
    img = new IMAGE;
    getimage(img, 0, 0, subBlockSize, subBlockSize);
    SetWorkingImage(); // 恢复默认工作区
}
