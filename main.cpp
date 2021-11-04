#include "includes/functions.hpp"

using namespace std;

void printBlockchainInfo(blockchainClass blockchain){
    ofstream out;
    out.open("output/blockchainResult.txt");

    for(int i=0; i<blockchain.blocks.size(); i++){
        char buff[20];
        strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&blockchain.blocks[i].timestamp));
        out << "-----------------------------------------------" << endl;
        out << "Block " << i << " info:" << endl;
        out << setw(30) << "Timestamp: " << buff << endl;
        out << setw(30) << "Number of transactions: " << blockchain.blocks[i].transactions.size() << endl;
        out << setw(30) << "Difficulty: " << blockchain.blocks[i].difficulty_target << endl;
        out << setw(30) << "Merkle root: " << blockchain.blocks[i].merkle_root_hash << endl;
        out << setw(30) << "Nonce: " << blockchain.blocks[i].nonce << endl;
        out << setw(30) << "Version: " << blockchain.blocks[i].version << endl;

    }
}

int main(){
    int difficultyTarget = 3;
    vector<userClass> users = generateUsers(500);
    vector<transactionClass> transactions = generateTransactions(1000, users);
    blockchainClass blockchain;

    // Find new block
    while(transactions.size() > 0){
        cout << "Mining block: " << blockchain.blocks.size() << endl;

        block_mining(transactions, blockchain, users, difficultyTarget);
        cout << "Liko transactionu: " << transactions.size();
    }

    printBlockchainInfo(blockchain);
}