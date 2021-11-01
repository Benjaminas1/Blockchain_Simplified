#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std;

class userClass{
    public:
        string name;
        string public_key;
        int balance;
};

class transactionClass{
    public:
        string transaction_ID_hash;
        string sender_public_key;
        string receiver_public_key;
        int amount;
};

class blockClass{
    public:
        string blockHash;
        string prev_block_hash;
        time_t timestamp;
        string version;
        string merkle_root_hash;
        unsigned int nonce;
        int difficulty_target;
        vector<transactionClass> transactions;
};

class blockchainClass{
    public:
        vector<blockClass> blocks;
};

string hashString(string inputStr);

int generateRandomNumber(int min, int max);

vector<userClass> generateUsers(int quantity);

vector<transactionClass> generateTransactions(int quantity, vector<userClass> user);

blockClass generateBlock(vector<transactionClass> &transactions, int nonce, blockchainClass blockchain, int difficulty);