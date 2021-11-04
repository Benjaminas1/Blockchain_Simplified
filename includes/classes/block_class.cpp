#include "block_class.hpp"
#include <fstream>

blockClass::blockClass(vector<transactionClass> transactions, string merkleRootHash, string version)
{
    this->transactions = transactions;
    this->version = version;
    this->merkle_root_hash = merkleRootHash;
}

// setters
void blockClass::addTransaction(transactionClass transaction)
{
    this->transactions.push_back(transaction);
}

void blockClass::updateBlock(int nonce, time_t timestamp, int difficulty, string prevBlockHash)
{
    this->nonce = nonce;
    this->timestamp = timestamp;
    this->difficulty_target = difficulty;
    this->prev_block_hash = prevBlockHash;
}

// getters
int blockClass::getMaxTransactionNumber()
{
    return max_transaction_number;
}

string blockClass::getMerkleRootHash()
{
    return merkle_root_hash;
}

vector<transactionClass> blockClass::getTransactions()
{
    return transactions;
}

// -- blockchain --
void blockchainClass::addBlock(blockClass block)
{
    blocks.push_back(block);
}

vector<blockClass> blockchainClass::getBlocks()
{
    return blocks;
}

