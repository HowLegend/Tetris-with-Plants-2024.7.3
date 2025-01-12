#pragma once
#include "AdvanceBlock.h"

// 方块 J
class Block_J : public AdvanceBlock
{
public:
	// 构造函数
	Block_J();
	// 析构函数
	~Block_J();


private:
	int typeInfo[4]; // 记录方块形状的参数 0 1
	//                                  2 3
	//                                  4 5
	//                                  6 7
};

