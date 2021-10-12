#include "includes/functions.hpp"

using namespace std;

int main(){
    vector<userStruct> users = generateUsers(1000);
    vector<transactionStruct> transactions = generateTransactions(10000, users);
    putTransactionsToBlock(transactions);
}