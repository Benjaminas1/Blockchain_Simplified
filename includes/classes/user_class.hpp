#pragma once

#include "../includes.hpp"

class userClass
{
private:
    string name;
    string public_key;
    int balance;

public:
    userClass(string name, string public_key, int balance);
    string getName();
    string getPublicKey();
    int getBalance();
    void setBalance(int new_balance);
};