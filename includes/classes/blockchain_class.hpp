#pragma once

#include "../includes.hpp"
#include "block_class.hpp"

class blockchainClass
{
private:
    vector<blockClass> blocks;

public:
    void addBlock(blockClass block);
    vector<blockClass> getBlocks();
    void printBlockchain();
};