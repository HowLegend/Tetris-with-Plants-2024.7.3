#pragma once
#include "AdvanceBlock.h"

// ���� T
class Block_T : public AdvanceBlock
{
public:
	// ���캯��
	Block_T();
	// ��������
	~Block_T();


private:
	int typeInfo[4]; // ��¼������״�Ĳ��� 0 1
	//                                  2 3
	//                                  4 5
	//                                  6 7
};

