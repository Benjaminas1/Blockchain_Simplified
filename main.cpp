#include "includes/functions.hpp"

using namespace std;

int main()
{   
    int difficultyTarget = 3;
    vector<userClass> users = generateUsers(500);
    vector<transactionClass> transactions = generateTransactions(1000, users);
    blockchainClass blockchain;

    // Find new block
    while (transactions.size() > 0)
    {
        cout << "Mining block: " << blockchain.getBlocks().size() << endl;

        block_mining(transactions, blockchain, users, difficultyTarget);
        cout << "----------------------------------" << endl;
    }

    blockchain.printBlockchain();
}