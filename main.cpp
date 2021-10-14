#include "includes/functions.hpp"

using namespace std;

int main(){
    int difficultyTarget = 4;
    vector<userClass> users = generateUsers(1000);
    vector<transactionClass> transactions = generateTransactions(10000, users);

    blockchainClass blockchain;
    // Find new block
    while(true){
        unsigned int number = generateRandomNumber(0, UINT_MAX);
        string hashedNumber = hashString(to_string(number));
        int zerosFound = 0;

        for(int i=0; i<difficultyTarget; i++){
            if(hashedNumber[i] == '0') zerosFound++;
        }

        if(zerosFound == difficultyTarget){
            blockchain.blocks.push_back(generateBlock(transactions, number));
        }
    }

}