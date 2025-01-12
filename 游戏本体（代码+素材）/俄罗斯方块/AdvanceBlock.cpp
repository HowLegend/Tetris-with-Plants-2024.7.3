#include "AdvanceBlock.h"

AdvanceBlock::AdvanceBlock()
	:img(NULL)
{
	
}

AdvanceBlock::~AdvanceBlock()
{
	delete img;
	img = NULL;
}

void AdvanceBlock::draw(int leftMargin, int topMargin)
{
	for (int i = 0; i < 4; i++)
	{
		int x = leftMargin + subBlocks[i].col * subBlockSize;	   // ���x����
		int y = topMargin + (subBlocks[i].row + 3) * subBlockSize; // ���y����
		putimage(x, y, img);
	}
}

int AdvanceBlock::getBlockType()
{
	return blockType;
}