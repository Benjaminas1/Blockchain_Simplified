#pragma once

#include "../includes.hpp"
#include "transaction_class.hpp"

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