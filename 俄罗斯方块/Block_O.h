#pragma once
#include "AdvanceBlock.h"

// ���� O
class Block_O : public AdvanceBlock
{
public:
	// ���캯��
	Block_O();
	// ��������
	~Block_O();


private:
	int typeInfo[4]; // ��¼������״�Ĳ��� 0 1
	//                                  2 3
	//                                  4 5
	//                                  6 7
};

