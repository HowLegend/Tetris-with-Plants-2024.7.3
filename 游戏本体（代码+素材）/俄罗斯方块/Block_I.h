#pragma once
#include "AdvanceBlock.h"


// ���� I
class Block_I : public AdvanceBlock
{
public:
	// ���캯��
	Block_I();
	// ��������
	~Block_I();


private:
	int typeInfo[4]; // ��¼������״�Ĳ��� 0 1
	//                                  2 3
	//                                  4 5
	//                                  6 7
};

