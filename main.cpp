#include "includes/functions.hpp"

using namespace std;

int main(){
    int difficultyTarget = 3;
    vector<userClass> users = generateUsers(500);
    vector<transactionClass> transactions = generateTransactions(1000, users);

    blockchainClass blockchain;

    // Find new block
    while(transactions.size() > 0){
        cout << "Mining block: " << blockchain.blocks.size() << endl;

        while(true){
            
            unsigned int number = generateRandomNumber(0, UINT_MAX);
            string hashedNumber = hashString(to_string(number));
            int zerosFound = 0;

            for(int i=0; i<difficultyTarget; i++){
                if(hashedNumber[i] == '0') zerosFound++;
            }

            if(zerosFound == difficultyTarget){
                blockchain.blocks.push_back(generateBlock(transactions, number, blockchain, difficultyTarget, users));
                break;
            }
        }
    }

    printBlockchainInfo(blockchain);

}