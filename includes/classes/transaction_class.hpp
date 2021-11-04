#pragma once

#include "../includes.hpp"

class transactionClass
{
private:
    string transaction_ID_hash;
    string sender_public_key;
    string receiver_public_key;
    int amount;

public:
    transactionClass(string transaction_ID_hash,
                     string sender_public_key,
                     string receiver_public_key,
                     int amount);
    string getTransactionIdHash();
    string getSenderPublicKey();
    string getReceiverPublicKey();
    int getAmount();
};