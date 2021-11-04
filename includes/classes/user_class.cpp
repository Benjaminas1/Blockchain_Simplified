#include "user_class.hpp"

userClass::userClass(string name, string public_key, int balance){
    this->name = name;
    this->public_key = public_key;
    this->balance = balance;
}

string userClass::getName()
{
    return name;
}

string userClass::getPublicKey()
{
    return public_key;
}

int userClass::getBalance()
{
    return balance;
}

void userClass::setBalance(int new_balance)
{
    if (new_balance >= 0)
        balance = new_balance;
}