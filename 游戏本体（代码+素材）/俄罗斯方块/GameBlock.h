#pragma once
#include "Block.h"
#include "AdvanceBlock.h"

class GameBlock : public Block
{
public:
    // ���캯��
    GameBlock();
    // ���ι��캯��  ���ݲ�������������Ϣ���г�ʼ��  ���ڶ�ȡ�浵�ķ���  �����ʽ������ + 8��λ�����������
    GameBlock(int* blockInfo);
    // �������캯�� ��������Ԥ�淽�������
    GameBlock(Block* other);
    // ��������
    ~GameBlock();
    // ����=
    GameBlock& operator=(const GameBlock& other);

    // ��������,������Ϸ�߽�
    void draw(int leftMargin, int topMargin);
    // �����һ���ӿ� ���ڻ�÷�������
    int getBlockType();

private:
    IMAGE* img; // ��һ��ָ��ָ��ͬһ��ͼƬ��subBlock��,��ʶ�÷������Ͷ�Ӧ��ͼƬ
};
