#include "Block.h"

// ��̬��Ա������ʼ��
IMAGE* Block::imgs[7] = {
    NULL,
};
int Block::subBlockSize = 27;

Block::Block()
{
    // ��ʼ��blockType
    blockType = 0;

    // ��ʼ��subBlocks
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
    // �� imgs[0]-imgs[6] ���߸�ָ����и�ֵ,subBlock
    // ���� subBlock ͼƬ
    IMAGE tempImg;
    if (bk == "bk1")
    {
        loadimage(&tempImg, "./materials/subBlock_1.png", 216, 27);
    }
    else if (bk == "bk2")
    {
        loadimage(&tempImg, "./materials/subBlock_2.png", 216, 27);
    }
    // ��ȡͼƬ
    SetWorkingImage(&tempImg); // ���ò�������
    for (int i = 0; i < 7; i++)
    {
        imgs[i] = new IMAGE;
        getimage(imgs[i], i * subBlockSize, 0, subBlockSize, subBlockSize);
    }
    SetWorkingImage(); // �ָ�Ĭ�Ϲ�����
}

void Block::drop()
{
    for (Point& sBlock : subBlocks) // ���ô�ֵ
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
    // ֱ��������ѧ��ʽ���ۣ�ʵ���߼��ϵ���ת
    Point centerPoint = subBlocks[1]; // ��ת����
    for (Point& rotatePoint : subBlocks)
    {
        Point oldRotatePoint = rotatePoint;
        rotatePoint.col = centerPoint.col - oldRotatePoint.row + centerPoint.row;
        rotatePoint.row = centerPoint.row + oldRotatePoint.col - centerPoint.col;
    }
}

bool Block::isInMapLegally(const vector<vector<int>>& map) const
{
    // ��ȡmap�ı߽�rows��cols
    int rows = map.size();
    int cols = map[0].size();
    // �ж�
    for (int i = 0; i < 4; i++)
    {
        if (subBlocks[i].row < 0) // �����ɵķ��飬����subBlock��û����
            continue;
        if (subBlocks[i].row < 0 || subBlocks[i].row >= rows ||                                             // ���� ��
            subBlocks[i].col < 0 || subBlocks[i].col >= cols ||                                             // ���� ��
            (map[subBlocks[i].row][subBlocks[i].col] != 0 && map[subBlocks[i].row][subBlocks[i].col] != 8)) // ���� ������������û���ص�
        {
            return false;
        }
    }
    return true;
}

void Block::solidify(vector<vector<int>>& map) const
{
    // �������������������д��map
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
