#pragma once
#include "AdvanceBlock.h"

// ���� J
class Block_J : public AdvanceBlock
{
public:
	// ���캯��
	Block_J();
	// ��������
	~Block_J();


private:
	int typeInfo[4]; // ��¼������״�Ĳ��� 0 1
	//                                  2 3
	//                                  4 5
	//                                  6 7
};

