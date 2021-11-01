#include "functions.hpp"

void initialiseHash(int *hashed){

    string hash = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"; //Has to be 64 symbols

    if(hash.length() != 64){
        cout << "Error: primary hash size is not 64" << endl;
        exit(0);
    }

    for(int i=0; i<64; i++){
        hashed[i] = 0;
        if(isdigit(hash[i])) hashed[i] = (int)hash[i] - 48;
        else hashed[i] = (int)hash[i] - 87;
        //cout << hashed[i] << " ";
    }
    
}

string hashToString(int hashed[]){
    string hash = "";

    //Converting numbers into characters and adding to 'hash' string
    for(int i=0; i < 64; i++){
        if(hashed[i] < 10) hash += to_string(hashed[i]);
        else hash += hashed[i] + 87;
    }
    return hash;
}

string hashString(string inputStr){
    int hashed[64];
    initialiseHash(hashed);

    if(inputStr == "") return "86ce601b0fa462069209e0b382631dcff298ca0e1f3ac1b45f162649c952fa57"; // Empty hash

    vector<int> allIntSums;
    int fullSum = 0;

    // Fixing same hashes when all symbols are the same, or when there is only single symbol
    bool allSymbolsSame = true;
    for(int i=0; i<inputStr.length()-1; i++){
        if(inputStr[i]!=inputStr[i+1]){
            allSymbolsSame = false;
            break;
        }
    }
    if(allSymbolsSame == true || inputStr.length() == 1) inputStr += "[2a.re]'/fdfe.w[ro[]o23v,pw/]ad" + inputStr[0];

    // Filling vector with calculated numbers and counting sum
    for(int i=0; i<inputStr.length(); i++){
        //Convert letter to int using ascii
        int number = (int)inputStr[i];

        allIntSums.push_back(number);
        fullSum += number;
    }

    if(inputStr.length() < 64){
        for(int i=0; i<64;){
            for(int inputStrIndex = 0; inputStrIndex<allIntSums.size(); inputStrIndex++){
                if(i + inputStrIndex <= 64){
                    hashed[i] += fullSum + allIntSums[inputStrIndex];
                    hashed[i] = hashed[i]%16;
                    if(hashed[i]<0) hashed[i] = -hashed[i];
                    i++;
                }
                else break;
            }
        }
    }
    else{
        int hashedIndex = 0;
        for(int i = 0; i<allIntSums.size(); i++){
            if(i % 64 == 0 && i != 0){
                hashedIndex = 0;
                fullSum = 0;
            }
            hashed[hashedIndex] += fullSum + allIntSums[i];
            hashed[hashedIndex] = hashed[hashedIndex]%16;
            if(hashed[hashedIndex]<0) hashed[hashedIndex] = -hashed[hashedIndex];
            hashedIndex++;
        }
    }
    
    return hashToString(hashed);
}

std::random_device dev;
int generateRandomNumber(int min, int max){
    
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min,max); // distribution in range [1, 6]

    return dist6(rng);
}

vector<userClass> generateUsers(int quantity){
    vector<userClass> users;

    for(int i=0; i<quantity; i++){
        userClass newUser;
        newUser.name = "Name" + to_string(i);
        newUser.public_key = hashString(newUser.name);
        newUser.balance = generateRandomNumber(100,1000000);

        users.push_back(newUser);
    }

    return users;
}

vector<transactionClass> generateTransactions(int quantity, vector<userClass> user){
    vector<transactionClass> transactions;

    for(int i=0; i<quantity; i++){
        transactionClass newTransaction;

        newTransaction.transaction_ID_hash = hashString("transaction_id_" + to_string(i));
        int sender_id = generateRandomNumber(0,999);
        newTransaction.sender_public_key = user[sender_id].public_key;
        newTransaction.receiver_public_key = user[generateRandomNumber(0,999)].public_key;
        newTransaction.amount = user[sender_id].balance / 10;

        transactions.push_back(newTransaction);
    }

    return transactions;
}

void putTransactionsToBlock(vector<transactionClass> &transactions, blockClass &block){
    for(int i=0; i<100; i++){
        if(transactions.size() == 0) break;
        int transactionID = generateRandomNumber(0,transactions.size() - 1);
        block.transactions.push_back(transactions[transactionID]);
        transactions.erase(transactions.begin() + transactionID);
    }
}

string getMerkleRoot(vector<transactionClass> transactions){
    vector<string> currentLayer;

    for(auto transaction : transactions){    
        currentLayer.push_back(transaction.transaction_ID_hash);
    }

    while(currentLayer.size() > 1) {
        vector<string> tempLayer;
        // Fixing uneven node size
        if(currentLayer.size() % 2 != 0) currentLayer.push_back(currentLayer.back());

        for(int i=0; i<currentLayer.size(); i += 2){
            string combinedHash = hashString(currentLayer[i] + currentLayer[i + 1]);
            tempLayer.push_back(combinedHash);
        }

        currentLayer = tempLayer;
    }
    
    return currentLayer[0];
}

blockClass generateBlock(vector<transactionClass> &transactions, int nonce, blockchainClass blockchain, int difficulty){
    blockClass block;
    putTransactionsToBlock(transactions, block);
    block.nonce = nonce;
    block.timestamp = time(0);
    block.version = "v0.1";
    block.merkle_root_hash = getMerkleRoot(block.transactions);
    block.difficulty_target = difficulty;

    block.blockHash = hashString(to_string(nonce));
    if(blockchain.blocks.size() == 0) block.prev_block_hash = "none";
    else block.prev_block_hash = blockchain.blocks.back().blockHash;

    return block;
}

void blockMining(){
    
}