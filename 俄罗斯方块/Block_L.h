#pragma once
#include "AdvanceBlock.h"

// ���� L
class Block_L : public AdvanceBlock
{
public:
	// ���캯��
	Block_L();
	// ��������
	~Block_L();


private:
	int typeInfo[4]; // ��¼������״�Ĳ��� 0 1
	//                                  2 3
	//                                  4 5
	//                                  6 7
};

