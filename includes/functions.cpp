#include "functions.hpp"
#include "hash.hpp"

std::random_device device;
int generateRandomNumber(int min, int max)
{

    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(generator);
}

vector<userClass> generateUsers(int quantity)
{
    vector<userClass> users;

    for (int i = 0; i < quantity; i++)
    {
        string name = "Name" + to_string(i);
        userClass newUser(
            name,
            hashString(name),
            generateRandomNumber(100, 1000000));

        users.push_back(newUser);
    }

    return users;
}

vector<transactionClass> generateTransactions(int quantity, vector<userClass> user)
{
    vector<transactionClass> transactions;

    for (int i = 0; i < quantity; i++)
    {

        int sender_id = generateRandomNumber(0, user.size() - 1);
        int receiver_id = generateRandomNumber(0, user.size() - 1);

        string sender_public_key = user[sender_id].getPublicKey();
        string receiver_public_key = user[receiver_id].getPublicKey();
        int amount = generateRandomNumber(1000, 100000);
        string transaction_ID_hash = hashString(sender_public_key + receiver_public_key + to_string(amount));

        transactionClass newTransaction(transaction_ID_hash, sender_public_key, receiver_public_key, amount);
        transactions.push_back(newTransaction);
    }

    return transactions;
}

int find_user_index_by_key(string publicKey, vector<userClass> users)
{
    int i = 0;
    for (auto user : users)
    {
        if (user.getPublicKey() == publicKey)
            return i;
        i++;
    }
    return -1;
}

void remove_transaction_from_transactions(vector<transactionClass> &transactions, transactionClass blockTransaction)
{
    transactions.erase(
        remove_if(transactions.begin(), transactions.end(), [&](transactionClass &transaction)
                  { return transaction.getTransactionIdHash() == blockTransaction.getTransactionIdHash(); }),
        transactions.end());
}

void validateTransactions(vector<transactionClass> &transactions, blockClass block, vector<userClass> &users)
{
    for (int i = 0; i < block.getTransactions().size(); i++)
    {
        int senderIndex = find_user_index_by_key(block.getTransactions()[i].getSenderPublicKey(), users);
        int receiverIndex = find_user_index_by_key(block.getTransactions()[i].getReceiverPublicKey(), users);
        bool transactionIsValid = (senderIndex != -1 && receiverIndex != -1 && block.getTransactions()[i].getAmount() <= users[senderIndex].getBalance() && block.getTransactions()[i].getAmount() >= 0) ? true : false;

        string transactionInfo = block.getTransactions()[i].getSenderPublicKey() + block.getTransactions()[i].getReceiverPublicKey() + to_string(block.getTransactions()[i].getAmount());
        bool transactionInfoUnchanged = (block.getTransactions()[i].getTransactionIdHash() == hashString(transactionInfo)) ? true : false;

        if (transactionIsValid && transactionInfoUnchanged)
        {
            int amount = block.getTransactions()[i].getAmount();
            int sender_balance = users[senderIndex].getBalance();
            int receiver_balance = users[receiverIndex].getBalance();
            users[senderIndex].setBalance(sender_balance - amount);
            users[receiverIndex].setBalance(sender_balance + amount);
        }

        remove_transaction_from_transactions(transactions, block.getTransactions()[i]);
    }
}

string getMerkleRoot(vector<transactionClass> transactions)
{
    vector<string> currentLayer;

    for (auto transaction : transactions)
    {
        currentLayer.push_back(transaction.getTransactionIdHash());
    }

    while (currentLayer.size() > 1)
    {
        vector<string> tempLayer;
        // Fixing uneven node size
        if (currentLayer.size() % 2 != 0)
            currentLayer.push_back(currentLayer.back());

        for (int i = 0; i < currentLayer.size(); i += 2)
        {
            string combinedHash = hashString(currentLayer[i] + currentLayer[i + 1]);
            tempLayer.push_back(combinedHash);
        }

        currentLayer = tempLayer;
    }

    return currentLayer[0];
}

blockClass generateBlock(vector<transactionClass> &transactions)
{
    vector<transactionClass> transactionsVector;
    for (int i = 0; i < 100; i++)
    {
        if (transactions.size() < 0)
            break;

        transactionsVector.push_back(transactions[i]);
    }
    blockClass block(transactionsVector, "v0.2", getMerkleRoot(transactions));

    return block;
}

void update_and_add_to_blockchain(blockClass &block, blockchainClass &blockchain, unsigned int nonce, int difficulty)
{
    string prev_block_hash;

    if (blockchain.getBlocks().size() == 0)
        prev_block_hash = "none";
    else
        prev_block_hash = blockchain.getBlocks().back().getMerkleRootHash();

    block.updateBlock(nonce, time(0), difficulty, prev_block_hash);

    blockchain.addBlock(block);
}

void block_mining(vector<transactionClass> &transactions, blockchainClass &blockchain, vector<userClass> &users, int difficultyTarget)
{
    int potentialBlocksCount = 5;
    vector<blockClass> potentialBlocks;

    for (int i = 0; i < potentialBlocksCount; i++)
    {
        potentialBlocks.push_back(generateBlock(transactions));
    }

    while (true)
    {
        for (int blockIndex = 0; blockIndex < potentialBlocksCount; blockIndex++)
        {
            for (int tryNr = 0; tryNr < 4000; tryNr++)
            {
                unsigned int number = generateRandomNumber(0, INT_MAX);
                string hashedNumber = hashString(to_string(number));
                int zerosFound = 0;

                for (int i = 0; i < difficultyTarget; i++)
                {
                    if (hashedNumber[i] == '0')
                        zerosFound++;
                }

                if (zerosFound == difficultyTarget)
                {
                    cout << "Success, winner block: " << blockIndex << endl;
                    validateTransactions(transactions, potentialBlocks[blockIndex], users);
                    update_and_add_to_blockchain(potentialBlocks[blockIndex], blockchain, number, difficultyTarget);
                    return;
                }
            }
        }
        cout << "- All blocks failed, reducing difficulty -" << endl;
        difficultyTarget -= 1;
    }
}