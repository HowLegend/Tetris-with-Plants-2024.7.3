#pragma once
#include <easyx.h>
#include "Block.h"


enum Plants
{
	IceShroom,  // ������
	CherryBoom, // ӣ��ը��
	plantCount  // ��Ŀͳ��
};

// ֲ����
class PlantsPower
{
public:
	// ���캯��
	PlantsPower();
	// ��������
	~PlantsPower();

	// ����ͼƬ
	void loadResource();
	// ����ֲ�￨��
	void showPlantCards();
	// ʹ�ú�������չʾ����
	void draw_Ice(int leftMargin, int topMargin, int subBlockSize, Block* curBlock);
	// ʹ��ӣ��ը����չʾ��ըͼƬ
	void draw_Boom(int leftMargin, int topMargin, int subBlockSize, Block* curBlock, vector<vector<int>>& map);

private:
	IMAGE* plantCardImg[plantCount];
	IMAGE* plantEffect[plantCount];
};

