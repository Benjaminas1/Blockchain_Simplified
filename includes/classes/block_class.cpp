#include "block_class.hpp"
#include <fstream>

blockClass::blockClass(vector<transactionClass> transactions, string merkleRootHash, string version)
{
    this->transactions = transactions;
    this->version = version;
    this->merkle_root_hash = merkleRootHash;
}

// setters
void blockClass::addTransaction(transactionClass transaction)
{
    this->transactions.push_back(transaction);
}

void blockClass::updateBlock(int nonce, time_t timestamp, int difficulty, string prevBlockHash)
{
    this->nonce = nonce;
    this->timestamp = timestamp;
    this->difficulty_target = difficulty;
    this->prev_block_hash = prevBlockHash;
}

// getters
int blockClass::getMaxTransactionNumber()
{
    return max_transaction_number;
}

string blockClass::getMerkleRootHash()
{
    return merkle_root_hash;
}

vector<transactionClass> blockClass::getTransactions()
{
    return transactions;
}

void blockClass::printBlockInfo(int index)
{
    ofstream out;
    if (index == 0)
    {
        out.open("../output/blocks_info.txt");
        out.close();
    }
    out.open("../output/blocks_info.txt", ios::app);

    char buff[20];
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
    out << "-----------------------------------------------" << endl;
    out << "Block " << index << " info:" << endl;
    out << setw(30) << "Timestamp: " << buff << endl;
    out << setw(30) << "Number of transactions: " << transactions.size() << endl;
    out << setw(30) << "Difficulty: " << difficulty_target << endl;
    out << setw(30) << "Merkle root: " << merkle_root_hash << endl;
    out << setw(30) << "Nonce: " << nonce << endl;
    out << setw(30) << "Version: " << version << endl << endl;
    out << "Block " << index << " transactions:" << endl;

    for (auto transaction : transactions)
    {
        if(transaction.getSenderPublicKey() == "") break;
        out << transaction.getSenderPublicKey() << " -> " << transaction.getReceiverPublicKey() << "   amount: " << transaction.getAmount() << endl;
    }
}