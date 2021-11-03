#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <algorithm>

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
        string prev_block_hash = "";
        string hash = "";
        time_t timestamp = 0;
        string version = "";
        string merkle_root_hash = "";
        unsigned int nonce = 0;
        int difficulty_target = 0;
        vector<transactionClass> transactions;
        const int max_transaction_number = 100;
};

class blockchainClass{
    public:
        vector<blockClass> blocks;
};

string hashString(string inputStr);

int generateRandomNumber(int min, int max);

vector<userClass> generateUsers(int quantity);

vector<transactionClass> generateTransactions(int quantity, vector<userClass> user);

blockClass addBlockToBlockchain(vector<transactionClass> &transactions, int nonce, blockchainClass blockchain, int difficulty, vector<userClass> &users);

void block_mining(vector<transactionClass> &transactions, blockchainClass &blockchain, vector<userClass> &users, int difficultyTarget);