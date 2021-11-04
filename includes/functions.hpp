#pragma once

#include "includes.hpp"
#include "classes/user_class.hpp"
#include "classes/transaction_class.hpp"
#include "classes/block_class.hpp"

string hashString(string inputStr);

int generateRandomNumber(int min, int max);

vector<userClass> generateUsers(int quantity);

vector<transactionClass> generateTransactions(int quantity, vector<userClass> user);

blockClass addBlockToBlockchain(vector<transactionClass> &transactions, int nonce, blockchainClass blockchain, int difficulty, vector<userClass> &users);

void block_mining(vector<transactionClass> &transactions, blockchainClass &blockchain, vector<userClass> &users, int difficultyTarget);