#pragma once
#include "AdvanceBlock.h"

// ���� S
class Block_S : public AdvanceBlock
{
public:
	// ���캯��
	Block_S();
	// ��������
	~Block_S();


private:
	int typeInfo[4]; // ��¼������״�Ĳ��� 0 1
	//                                  2 3
	//                                  4 5
	//                                  6 7
};
