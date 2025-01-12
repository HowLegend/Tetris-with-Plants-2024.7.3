#include "BlockProducer.h"

BlockProducer::BlockProducer()
{
}

BlockProducer::~BlockProducer()
{
}

Block* BlockProducer::createBlock(int blockTypeNum)
{
    switch (blockTypeNum)
    {
    case 1:
        return new Block_I();
    case 2:
        return new Block_S();
    case 3:
        return new Block_Z();
    case 4:
        return new Block_T();
    case 5:
        return new Block_L();
    case 6:
        return new Block_J();
    case 7:
        return new Block_O();
    default:
        return NULL;
    }
}