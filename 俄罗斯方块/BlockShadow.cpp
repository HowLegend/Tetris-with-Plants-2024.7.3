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

void BlockShadow::beShadowOf(Block* body)
{
    blockType = 8;              // ����Ϊ8��Ӱ�ӣ�
    for (int i = 0; i < 4; i++) // ����λ��
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
            int x = leftMargin + subBlocks[i].col * subBlockSize; // ���x����
            int y = topMargin + subBlocks[i].row * subBlockSize;  // ���y����
            putimage(x, y, img);                                  // �ڣ�x��y��������ͼ��
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
    // ���롰Ӱ�ӡ�ͼ��
    // �� imgs[7] ָ����и�ֵ,shadowBlock
    loadimage(&tempImg, "./materials/shadowBlock.png", 27, 27);
    // ��ȡͼƬ
    SetWorkingImage(&tempImg); // ���ò�������
    img = new IMAGE;
    getimage(img, 0, 0, subBlockSize, subBlockSize);
    SetWorkingImage(); // �ָ�Ĭ�Ϲ�����
}
