#pragma once

#include "../includes.hpp"
#include "transaction_class.hpp"
#include "user_class.hpp"

class blockClass
{
private:
    string prev_block_hash = "";
    string hash = "";
    time_t timestamp = 0;
    string version = "";
    string merkle_root_hash = "";
    unsigned int nonce = 0;
    int difficulty_target = 0;
    vector<transactionClass> transactions;
    const int max_transaction_number = 100;

public:
    blockClass(vector<transactionClass> transactions, string merkleRootHash, string version); // constructor
    // setters
    void addTransaction(transactionClass transaction);
    void updateBlock(int nonce, time_t timestamp, int difficulty, string prevBlockHash);
    // getters
    vector<transactionClass> getTransactions();
    int getMaxTransactionNumber();
    string getMerkleRootHash();

    time_t getTimeStamp() { return timestamp; };
    int getDifficulty() { return difficulty_target; };
    int getNonce() { return nonce; };
    string getVersion() { return version; };
};


class blockchainClass
{
private:
    vector<blockClass> blocks;

public:
    void addBlock(blockClass block);
    vector<blockClass> getBlocks();
};