#include "PlantsPower.h"
#include "tools.h"
#include <conio.h>
#include <mmsystem.h>

PlantsPower::PlantsPower()
{
	// 初始化数组
	for (int i = 0; i < plantCount; i++)
	{
		plantCardImg[i] = new IMAGE;
		plantEffect[i] = new IMAGE;
	}

	loadResource();
}

PlantsPower::~PlantsPower()
{
	// delete
	for (int i = 0; i < plantCount; i++)
	{
		delete plantCardImg[i];
		delete plantEffect[i];
	}
	
}

void PlantsPower::loadResource()
{
	// 导入卡牌
	loadimage(plantCardImg[IceShroom], "./materials/plant/card_iceshroom.png");
	loadimage(plantCardImg[CherryBoom], "./materials/plant/card_cherryBoom.png");

	// 导入技能效果
	loadimage(plantEffect[IceShroom], "./materials/plant/icetrap.png");
	loadimage(plantEffect[CherryBoom], "./materials/plant/Boom.png", 220, 220);
}

void PlantsPower::showPlantCards()
{
	// 设置字体
	LOGFONT f;                         // 字体变量
	gettextstyle(&f);                  // 获取当前字体
	f.lfHeight = 40;                   // 字体高度
	f.lfWidth = 15;                    // 字体宽度
	f.lfQuality = ANTIALIASED_QUALITY; // 字体抗锯齿
	setbkmode(TRANSPARENT);            // 字体背景设为透明
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("楷体"));
	settextstyle(&f);
	settextcolor(RGB(0, 0, 0));

	putimage(340, 450, plantCardImg[IceShroom]);
	putimage(340, 550, plantCardImg[CherryBoom]);
}

void PlantsPower::draw_Ice(int leftMargin, int topMargin, int subBlockSize, Block* curBlock)
{
	Point* arr = curBlock->getSubBlockLocationArray();

	// 音效
	mciSendString("play ./materials/plant/frozen.mp3", 0, 0, 0);

	// 显示结冰图样
	for (int i = 0; i < 4; i++)
	{
		if(arr[i].row>=0)
		{
			int x = leftMargin + arr[i].col * subBlockSize - 15;	   // 算出x坐标
			int y = topMargin + arr[i].row * subBlockSize + 10;        // 算出y坐标
			putimagePNG(x, y, plantEffect[IceShroom]);
		}
	}
}

void PlantsPower::draw_Boom(int leftMargin, int topMargin, int subBlockSize, Block* curBlock, vector<vector<int>>& map)
{
	Point* arr = curBlock->getSubBlockLocationArray();

	// 音效
	mciSendString("play ./materials/plant/cherrybomb.mp3", 0, 0, 0);

	// 绘制爆炸图片
	int x = leftMargin + (arr[1].col - 3) * subBlockSize - 30;	   // 算出x坐标
	int y = topMargin + (arr[1].row - 1) * subBlockSize - 40;       // 算出y坐标
	putimagePNG(x, y, plantEffect[CherryBoom]);
	Sleep(1000);

	// 消除爆炸范围附近的方块
	for (int i = 0; i < 4; i++)
	{
		for (int j = arr[i].row - 2; j < arr[i].row + 3; j++)
		{
			for (int k = arr[i].col - 2; k < arr[i].col + 3; k++)
			{
				if (j >= 0 && j < map.size() && k >= 0 && k < map[0].size())
				{
					map[j][k] = 0;
				}
			}
		}
	}
}
