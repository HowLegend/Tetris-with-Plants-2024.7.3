#pragma once
#include "AdvanceBlock.h"

// ���� Z
class Block_Z : public AdvanceBlock
{
public:
	// ���캯��
	Block_Z();
	// ��������
	~Block_Z();


private:
	int typeInfo[4]; // ��¼������״�Ĳ��� 0 1
	//                                  2 3
	//                                  4 5
	//                                  6 7
};
