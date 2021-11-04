#include "functions.hpp"

void initialiseHash(int *hashed)
{

    string hash = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"; //Has to be 64 symbols

    if (hash.length() != 64)
    {
        cout << "Error: primary hash size is not 64" << endl;
        exit(0);
    }

    for (int i = 0; i < 64; i++)
    {
        hashed[i] = 0;
        if (isdigit(hash[i]))
            hashed[i] = (int)hash[i] - 48;
        else
            hashed[i] = (int)hash[i] - 87;
        //cout << hashed[i] << " ";
    }
}

string hashToString(int hashed[])
{
    string hash = "";

    //Converting numbers into characters and adding to 'hash' string
    for (int i = 0; i < 64; i++)
    {
        if (hashed[i] < 10)
            hash += to_string(hashed[i]);
        else
            hash += hashed[i] + 87;
    }
    return hash;
}

string hashString(string inputStr)
{
    int hashed[64];
    initialiseHash(hashed);

    if (inputStr == "")
        return "86ce601b0fa462069209e0b382631dcff298ca0e1f3ac1b45f162649c952fa57"; // Empty hash

    vector<int> allIntSums;
    int fullSum = 0;

    // Fixing same hashes when all symbols are the same, or when there is only single symbol
    bool allSymbolsSame = true;
    for (int i = 0; i < inputStr.length() - 1; i++)
    {
        if (inputStr[i] != inputStr[i + 1])
        {
            allSymbolsSame = false;
            break;
        }
    }
    if (allSymbolsSame == true || inputStr.length() == 1)
        inputStr += "[2a.re]'/fdfe.w[ro[]o23v,pw/]ad" + inputStr[0];

    // Filling vector with calculated numbers and counting sum
    for (int i = 0; i < inputStr.length(); i++)
    {
        //Convert letter to int using ascii
        int number = (int)inputStr[i];

        allIntSums.push_back(number);
        fullSum += number;
    }

    if (inputStr.length() < 64)
    {
        for (int i = 0; i < 64;)
        {
            for (int inputStrIndex = 0; inputStrIndex < allIntSums.size(); inputStrIndex++)
            {
                if (i + inputStrIndex <= 64)
                {
                    hashed[i] += fullSum + allIntSums[inputStrIndex];
                    hashed[i] = hashed[i] % 16;
                    if (hashed[i] < 0)
                        hashed[i] = -hashed[i];
                    i++;
                }
                else
                    break;
            }
        }
    }
    else
    {
        int hashedIndex = 0;
        for (int i = 0; i < allIntSums.size(); i++)
        {
            if (i % 64 == 0 && i != 0)
            {
                hashedIndex = 0;
                fullSum = 0;
            }
            hashed[hashedIndex] += fullSum + allIntSums[i];
            hashed[hashedIndex] = hashed[hashedIndex] % 16;
            if (hashed[hashedIndex] < 0)
                hashed[hashedIndex] = -hashed[hashedIndex];
            hashedIndex++;
        }
    }

    return hashToString(hashed);
}

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
        transactionClass newTransaction;

        int sender_id = generateRandomNumber(0, user.size() - 1);
        newTransaction.sender_public_key = user[sender_id].getPublicKey();
        newTransaction.receiver_public_key = user[generateRandomNumber(0, user.size() - 1)].getPublicKey();
        newTransaction.amount = generateRandomNumber(1000, 100000);
        string transactionInfo = newTransaction.sender_public_key + newTransaction.receiver_public_key + to_string(newTransaction.amount);
        newTransaction.transaction_ID_hash = hashString(transactionInfo);

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

void putTransactionsToBlock(vector<transactionClass> transactions, blockClass &block)
{
    for (int i = 0; i < block.max_transaction_number; i++)
    {
        if (i == transactions.size())
            break;

        //int transactionID = generateRandomNumber(0, transactions.size() - 1);

        block.transactions.push_back(transactions[i]);
    }
}

void remove_transaction_from_transactions(vector<transactionClass> &transactions, transactionClass blockTransaction)
{
    transactions.erase(
        remove_if(transactions.begin(), transactions.end(), [&](transactionClass const &transaction)
                  { return transaction.transaction_ID_hash == blockTransaction.transaction_ID_hash; }),
        transactions.end());
}

void validateTransactions(vector<transactionClass> &transactions, blockClass block, vector<userClass> &users)
{
    for (int i = 0; i < block.transactions.size(); i++)
    {
        int senderIndex = find_user_index_by_key(block.transactions[i].sender_public_key, users);
        int receiverIndex = find_user_index_by_key(block.transactions[i].receiver_public_key, users);
        bool transactionIsValid = (senderIndex != -1 && receiverIndex != -1 && block.transactions[i].amount <= users[senderIndex].getBalance() && block.transactions[i].amount >= 0) ? true : false;

        string transactionInfo = block.transactions[i].sender_public_key + block.transactions[i].receiver_public_key + to_string(block.transactions[i].amount);
        bool transactionInfoUnchanged = (block.transactions[i].transaction_ID_hash == hashString(transactionInfo)) ? true : false;

        if (transactionIsValid && transactionInfoUnchanged)
        {
            int amount = block.transactions[i].amount;
            int sender_balance = users[senderIndex].getBalance();
            int receiver_balance = users[receiverIndex].getBalance();
            users[senderIndex].setBalance(sender_balance - amount);
            users[receiverIndex].setBalance(sender_balance + amount);
        }

        remove_transaction_from_transactions(transactions, block.transactions[i]);
    }
}

string getMerkleRoot(vector<transactionClass> transactions)
{
    vector<string> currentLayer;

    for (auto transaction : transactions)
    {
        currentLayer.push_back(transaction.transaction_ID_hash);
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
    blockClass block;
    block.version = "v0.1";
    putTransactionsToBlock(transactions, block);
    block.merkle_root_hash = getMerkleRoot(block.transactions);

    return block;
}

void update_and_add_to_blockchain(blockClass &block, blockchainClass &blockchain, unsigned int nonce, int difficulty)
{
    block.nonce = nonce;
    block.timestamp = time(0);
    block.version = "v0.1";
    block.merkle_root_hash = getMerkleRoot(block.transactions);
    block.difficulty_target = difficulty;

    if (blockchain.blocks.size() == 0)
        block.prev_block_hash = "none";
    else
        block.prev_block_hash = blockchain.blocks.back().merkle_root_hash;

    blockchain.blocks.push_back(block);
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