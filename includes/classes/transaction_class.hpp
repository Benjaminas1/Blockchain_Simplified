#pragma once

#include "../includes.hpp"

class transactionClass{
    public:
        string transaction_ID_hash;
        string sender_public_key;
        string receiver_public_key;
        int amount;
};