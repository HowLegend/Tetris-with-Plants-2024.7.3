#include "Block_I.h"

Block_I::Block_I()
{
    // �趨���ͱ��
    blockType = 1;

    // ��ǰ�½��Ķ���˹�����imgָ��ָ����������������subBlock
    img = imgs[blockType - 1];

    // �÷������״��Ϣ
    typeInfo[0] = 1;
    typeInfo[1] = 3;
    typeInfo[2] = 5;
    typeInfo[3] = 7;

    // ��ʼ���ĸ� subBlocks λ��
    for (int i = 0; i < 4; i++)
    {
        int num = typeInfo[i];
        subBlocks[i].row = num / 2 - 3; // �ڵ�ͼ�⻺��������Ϸ����
        subBlocks[i].col = num % 2 + 4; // ����
    }
}

Block_I::~Block_I()
{
}
