#include "transaction_class.hpp"

transactionClass::transactionClass(string transaction_ID_hash,
                                   string sender_public_key,
                                   string receiver_public_key,
                                   int amount)
{
    this->transaction_ID_hash = transaction_ID_hash;
    this->sender_public_key = sender_public_key;
    this->receiver_public_key = receiver_public_key;
    this->amount = amount;
}

string transactionClass::getTransactionIdHash()
{
    return transaction_ID_hash;
}

string transactionClass::getSenderPublicKey()
{
    return sender_public_key;
}

string transactionClass::getReceiverPublicKey()
{
    return receiver_public_key;
}

int transactionClass::getAmount()
{
    return amount;
}