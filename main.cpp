#include "includes/functions.hpp"
#include <fstream>

using namespace std;

void printBlockchainInfo(blockchainClass blockchain)
{
    ofstream out;
    out.open("../output/blockchainResult.txt");
    
    for (int i = 0; i < blockchain.getBlocks().size(); i++)
    {
        char buff[20];
        time_t time = blockchain.getBlocks()[i].getTimeStamp();
        strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&time));
        out << "-----------------------------------------------" << endl;
        out << "Block " << i << " info:" << endl;
        out << setw(30) << "Timestamp: " << buff << endl;
        out << setw(30) << "Number of transactions: " << blockchain.getBlocks()[i].getTransactions().size() << endl;
        out << setw(30) << "Difficulty: " << blockchain.getBlocks()[i].getDifficulty() << endl;
        out << setw(30) << "Merkle root: " << blockchain.getBlocks()[i].getMerkleRootHash() << endl;
        out << setw(30) << "Nonce: " << blockchain.getBlocks()[i].getNonce() << endl;
        out << setw(30) << "Version: " << blockchain.getBlocks()[i].getVersion() << endl;
    }
    
}

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

    printBlockchainInfo(blockchain);
}