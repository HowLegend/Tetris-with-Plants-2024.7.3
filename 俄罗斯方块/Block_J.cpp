#include "Block_J.h"

Block_J::Block_J()
{
    // �趨���ͱ��
    blockType = 6;

    // ��ǰ�½��Ķ���˹�����imgָ��ָ����������������subBlock
    img = imgs[blockType - 1];

    // �÷������״��Ϣ
    typeInfo[0] = 3;
    typeInfo[1] = 5;
    typeInfo[2] = 7;
    typeInfo[3] = 6;

    // ��ʼ���ĸ� subBlocks λ��
    for (int i = 0; i < 4; i++)
    {
        int num = typeInfo[i];
        subBlocks[i].row = num / 2 - 3; // �ڵ�ͼ�⻺��������Ϸ����
        subBlocks[i].col = num % 2 + 4; // ����
    }
}

Block_J::~Block_J()
{
}
