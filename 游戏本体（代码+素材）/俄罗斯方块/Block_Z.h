#pragma once
#include "AdvanceBlock.h"

// 方块 Z
class Block_Z : public AdvanceBlock
{
public:
	// 构造函数
	Block_Z();
	// 析构函数
	~Block_Z();


private:
	int typeInfo[4]; // 记录方块形状的参数 0 1
	//                                  2 3
	//                                  4 5
	//                                  6 7
};
