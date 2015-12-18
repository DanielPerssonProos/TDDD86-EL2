#include <chrono>
#include <map>
#include <set>
#include "Key.h"
#include <vector>
#include <thread>
#include <bitset>
#include <fstream>
#include <cmath>

using namespace std;


pair<Key,set<int>> AddToSubsetSum(const pair<Key,set<int>>& L, Key& addedValue, int index) {
    set<int> returnedSet = L.second;
    returnedSet.insert(index);
    return pair<Key,set<int>>(L.first + addedValue,returnedSet);

}

string getDecryptedWord(set<int> rows) {
    string binaryString = "";
    for (int i = 0; i < N; ++i) {
        if (rows.find(i) != rows.end()) {
            binaryString += "1";
        } else {
            binaryString += "0";
        }
    }
    string resultString = "";
    for (int j = 0; j < N; j+=5) {
        string subSting = binaryString.substr(j,5);
        unsigned int letterValue = bitset<32>(subSting).to_ulong();
        resultString += ALPHABET[letterValue];
    }
    return resultString;
}

 set<int> getRowSet(Key rowCombination) {
     set<int> rowSet;
     for (int i = 0; i < N; ++i) {
         if (KEYbit(rowCombination, i)) {
             rowSet.insert(i);
         }
     }
     return rowSet;
 }

int
main(int argc, char* argv[]) {
    unsigned char buffer[C + 1];     // temporary string buffer
    Key candidate = {{0}};         // a password candidate
    Key encrypted;                 // the encrypted password
    Key candenc;                   // the encrypted password candidate
    Key zero = {{0}};              // the all zero key
    Key T[N];                      // the table T

    if (argc != 2) {
        cout << "Usage:" << endl << argv[0] << " password < rand8.txt" << endl;
        return 1;
    }

    encrypted = KEYinit((unsigned char *) argv[1]);

    for (int i = 0; i < N; ++i) {
        scanf("%s", buffer);
        T[i] = KEYinit(buffer);
    }

    auto begin = chrono::high_resolution_clock::now();

    vector<pair<Key,set<int>>> Sub1Vector;

    set<int> tempElement;
    string zeroString = "";
    for (int i = 0; i < C; ++i) {
        zeroString += "a";
    }
    //We insert the element containing only zero bits into the subset1 to be able to combine all rows in an efficient way.
    Sub1Vector.push_back(pair<Key,set<int>>(KEYinit((unsigned char *) zeroString.c_str()), tempElement));

    //The offset is used to balance memory allocation vs CPU usage
    int offset = 2;
    //We iterate through the first N/2 - offset rows
    for (int i = 0; i < N/2 -offset; ++i) {

        vector<pair<Key,set<int>>> temp1;
        for (vector<pair<Key,set<int>>>::iterator it = Sub1Vector.begin(); it != Sub1Vector.end(); ++it){
            pair<Key,set<int>> tempPair = AddToSubsetSum(*it, T[i] ,i);
            //We use a temp1 vector to store the values calculated to avoid iterating over the newly created subsets in this loop.
            temp1.push_back(tempPair);

        }
        for (vector<pair<Key,set<int>>>::iterator it = temp1.begin(); it != temp1.end(); ++it){
            //We can now push all the temp elements to the vector
            Sub1Vector.push_back(*it);
        }
    }

    //All combinations for the first subset has been generated.

    vector<string> result;

    multimap<Key, set<int>> Sub1;
    //In order to find elements quick we insert all the elements in the vector to a multimap.
    //The reason to use a multimap is because we can have the same key but different row combinations.
    Sub1.insert(Sub1Vector.begin(), Sub1Vector.end());
    Sub1Vector.clear();
    cout << "Half way there." << endl;


    //If we already generated the encrypted key from only the first subset we will find it here.
    auto foundValues = Sub1.equal_range(encrypted);
    for (auto i = foundValues.first; i != foundValues.second; ++i) {
        result.push_back(getDecryptedWord(i->second));
    }



    string combinationString = "";
    for (int i = 0; i < C-1; ++i) {
        combinationString += "a";
    }
    combinationString += "b";
    //Create a Key consisting of 0's and with the last bit as a 1
    Key rowCombination = KEYinit((unsigned char*) combinationString.c_str());

    //Runs 2 to the power of the number of rows remaining
    for (int i = 0; i < pow(2.0,N/2+(N%2)+offset)-1; ++i) {
        //Creates all possible combinations of rows in the second subset.
        Key subsetSum = KEYsubsetsum(rowCombination,T);

        //A decryption is found if the encrypted key - the generated key exists in the first subset
        foundValues = Sub1.equal_range(encrypted-subsetSum);
        //a set of rows of the current rowCombination value
        set<int> rowSet = getRowSet(rowCombination);
        for (auto i = foundValues.first; i != foundValues.second; ++i) {
            //inserts all found solutions into the result vector
            set<int> tempSet = i->second;
            tempSet.insert(rowSet.begin(),rowSet.end());
            result.push_back(getDecryptedWord(tempSet));
        }
        //increments the rowCombination with 1 bit.
        ++rowCombination;
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Decryption took " << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " milliseconds." << endl;


    cout << "Found possible passwords:" << endl;
    //Prints the possible encryped passwords
    for(int i =0; i < result.size();++i){
        cout << result[i] << endl;
    }
    return 0;
}
