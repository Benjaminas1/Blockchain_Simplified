#include "blockchain_class.hpp"

void blockchainClass::addBlock(blockClass block)
{
    blocks.push_back(block);
}

vector<blockClass> blockchainClass::getBlocks()
{
    return blocks;
}

void blockchainClass::printBlockchain()
{
    for (int i = 0; i < blocks.size(); i++)
    {
        blocks[i].printBlockInfo(i);
    }
}
