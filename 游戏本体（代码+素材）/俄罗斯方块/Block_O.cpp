#include "Block_O.h"

Block_O::Block_O()
{
    // �趨���ͱ��
    blockType = 7;

    // ��ǰ�½��Ķ���˹�����imgָ��ָ����������������subBlock
    img = imgs[blockType - 1];

    // �÷������״��Ϣ
    typeInfo[0] = 2;
    typeInfo[1] = 3;
    typeInfo[2] = 4;
    typeInfo[3] = 5;

    // ��ʼ���ĸ� subBlocks λ��
    for (int i = 0; i < 4; i++)
    {
        int num = typeInfo[i];
        subBlocks[i].row = num / 2 - 3; // �ڵ�ͼ�⻺��������Ϸ����
        subBlocks[i].col = num % 2 + 4; // ����
    }
}

Block_O::~Block_O()
{
}
