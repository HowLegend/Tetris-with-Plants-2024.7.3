#pragma once
#include "Block.h"

class AdvanceBlock : public Block
{
public:
    // ���캯��
    AdvanceBlock();
    // ��������
    ~AdvanceBlock();

    // ��������,������Ϸ�߽�
    void draw(int leftMargin, int topMargin);
    // �����һ���ӿ� ���ڻ�÷�������
    int getBlockType();

protected:
    IMAGE* img; // ÿ�������е�С��������ͬ�ģ�������һ��ָ��ָ��ͬһ��ͼƬ��subBlock���Ϳ�����
};
