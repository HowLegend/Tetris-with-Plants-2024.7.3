#pragma once
#include "Block_I.h"
#include "Block_J.h"
#include "Block_L.h"
#include "Block_O.h"
#include "Block_S.h"
#include "Block_T.h"
#include "Block_Z.h"

class BlockProducer
{
public:
	// ���캯��
	BlockProducer();
	// ��������
	~BlockProducer();
	// �������ṩ�·���
	Block* createBlock(int blockTypeNum);

private:
};

