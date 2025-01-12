#pragma once
#include "AdvanceBlock.h"

// 方块 L
class Block_L : public AdvanceBlock
{
public:
	// 构造函数
	Block_L();
	// 析构函数
	~Block_L();


private:
	int typeInfo[4]; // 记录方块形状的参数 0 1
	//                                  2 3
	//                                  4 5
	//                                  6 7
};

