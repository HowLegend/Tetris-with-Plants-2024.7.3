#pragma once
#include "AdvanceBlock.h"

// 方块 S
class Block_S : public AdvanceBlock
{
public:
	// 构造函数
	Block_S();
	// 析构函数
	~Block_S();


private:
	int typeInfo[4]; // 记录方块形状的参数 0 1
	//                                  2 3
	//                                  4 5
	//                                  6 7
};
