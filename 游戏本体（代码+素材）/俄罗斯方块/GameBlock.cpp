#include "GameBlock.h"

GameBlock::GameBlock()
{
    // ��ǰ�½��Ķ���˹�����imgָ��ָ����������������subBlock
    img = imgs[blockType - 1];
}

GameBlock::GameBlock(int* blockInfo)
{
    blockType = blockInfo[0];
    // ��ǰ�½��Ķ���˹�����imgָ��ָ����������������subBlock
    img = imgs[blockType - 1];
    // �����浵���ĸ� subBlocks λ��
    for (int i = 0; i < 4; i++)
    {
        subBlocks[i].row = blockInfo[2 * i + 1]; // �ڵ�ͼ�⻺��������Ϸ����
        subBlocks[i].col = blockInfo[2 * i + 2]; // ����
    }
}

GameBlock::GameBlock(Block* other)
{
    int otherBlockType = other->getBlockType();

    blockType = otherBlockType;     // ��������
    img = imgs[otherBlockType - 1]; // ����ͼ��

    // �����ĸ� subBlocks λ��
    Point* otherSubBlocks = other->getSubBlockLocationArray();
    for (int i = 0; i < 4; i++)
    {
        subBlocks[i] = otherSubBlocks[i];

        // int num = blocks[otherBlockType - 1][i];
        // subBlocks[i].row = num / 2 - 3; // �ڵ�ͼ�⻺��������Ϸ����
        // subBlocks[i].col = num % 2 + 4; // ����
    }
}

GameBlock::~GameBlock()
{
    delete img;
    img = NULL;
}

GameBlock& GameBlock::operator=(const GameBlock& other)
{
    if (this == &other) // ͨ���жϵ�ַ�Ƿ���ͬ������ֹ�Լ������Լ�
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
        this->img = other.img; // ����Ҫnewһ��������ָ��ͬԴ��ͼƬ�ز�
        return *this;
    }
}

void GameBlock::draw(int leftMargin, int topMargin)
{
    for (int i = 0; i < 4; i++)
    {
        if (subBlocks[i].row >= 0)
        {
            int x = leftMargin + subBlocks[i].col * subBlockSize; // ���x����
            int y = topMargin + subBlocks[i].row * subBlockSize;  // ���y����
            putimage(x, y, img);                                  // �ڣ�x��y��������ͼ��
        }
    }
}

int GameBlock::getBlockType()
{
    return blockType;
}
