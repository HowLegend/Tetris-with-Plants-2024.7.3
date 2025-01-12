#pragma once
#include <easyx.h>
#include "Block.h"


enum Plants
{
	IceShroom,  // 寒冰菇
	CherryBoom, // 樱桃炸弹
	plantCount  // 数目统计
};

// 植物类
class PlantsPower
{
public:
	// 构造函数
	PlantsPower();
	// 析构函数
	~PlantsPower();

	// 载入图片
	void loadResource();
	// 画出植物卡组
	void showPlantCards();
	// 使用寒冰菇，展示寒冰
	void draw_Ice(int leftMargin, int topMargin, int subBlockSize, Block* curBlock);
	// 使用樱桃炸弹，展示爆炸图片
	void draw_Boom(int leftMargin, int topMargin, int subBlockSize, Block* curBlock, vector<vector<int>>& map);

private:
	IMAGE* plantCardImg[plantCount];
	IMAGE* plantEffect[plantCount];
};

