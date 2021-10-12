#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

struct userStruct{
    string name;
    string public_key;
    int balance;
};

struct transactionStruct{
    string transaction_ID_hash;
    string sender_public_key;
    string receiver_public_key;
    int amount;
};

struct blockStruct{
    string prev_block_hash;
    time_t timestamp;
    string version;
    string merkel_root_hash;
    int nonce;
    int difficulty_arget;
    vector<transactionStruct> transactions;
};

string hashString(string inputStr);

vector<userStruct> generateUsers(int quantity);

vector<transactionStruct> generateTransactions(int quantity, vector<userStruct> user);

void putTransactionsToBlock(vector<transactionStruct> transactions);