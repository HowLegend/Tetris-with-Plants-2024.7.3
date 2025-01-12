#pragma once
#include "Block.h"
#include "GameBlock.h"

class BlockShadow : public Block
{
public:
    // ���캯��
    BlockShadow();
    // �вι��캯�� ����Ӱ�ӵ�body��һ����λ
    BlockShadow(Block* body);
    // ��������
    ~BlockShadow();

    // ����=
    BlockShadow& operator=(const BlockShadow& other);

    // ��Ϊbody�����Ӱ��shadow
    void beShadowOf(Block* body);
    // ��������,������Ϸ�߽�
    void draw(int leftMargin, int topMargin);
    // �����һ���ӿ� ���ڻ�÷�������
    int getBlockType();
    // ������ShadowImg��ͼƬ���þ�̬�������ؾ�̬��������Ϊ������չ���������ܡ�ʱ���ֻ�δ����block����Ҫ���ⲿ����ͼ��
    void lodShadowImg();

private:
    IMAGE* img; // ÿ�������е�С��������ͬ�ģ�������һ��ָ��ָ��ͬһ��ͼƬ��subBlock���Ϳ�����
};
