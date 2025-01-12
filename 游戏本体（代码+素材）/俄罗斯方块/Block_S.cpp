#include "Block_S.h"

Block_S::Block_S()
{
    // �趨���ͱ��
    blockType = 2;

    // ��ǰ�½��Ķ���˹�����imgָ��ָ����������������subBlock
    img = imgs[blockType - 1];

    // �÷������״��Ϣ
    typeInfo[0] = 2;
    typeInfo[1] = 4;
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

Block_S::~Block_S()
{
}
