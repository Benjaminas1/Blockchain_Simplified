#pragma once

#include "includes.hpp"
#include "classes/user_class.hpp"
#include "classes/transaction_class.hpp"
#include "classes/block_class.hpp"

vector<userClass> generateUsers(int quantity);

vector<transactionClass> generateTransactions(int quantity, vector<userClass> user);

void block_mining(vector<transactionClass> &transactions, blockchainClass &blockchain, vector<userClass> &users, int difficultyTarget);