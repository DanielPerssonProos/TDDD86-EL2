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
    /*cout << "Rows: ";
    for (int row : rows) {
        cout << "," << row;
    }
    cout << endl;*/
    string binaryString = "";
    for (int i = 0; i < N; ++i) {
        if (rows.find(i) != rows.end()) {
            binaryString += "1";
        } else {
            binaryString += "0";
        }
    }
    //cout << "Binary string: " << binaryString << endl;
    string resultString = "";
    for (int j = 0; j < N; j+=5) {
        string subSting = binaryString.substr(j,5);
        //cout << "Substring " << subSting << endl;
        unsigned int letterValue = bitset<32>(subSting).to_ulong();
        //cout << letterValue << endl;
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
/*
    ofstream myfile;
    myfile.open ("rand9.txt");
    for(int k = 0; k < N;++k){
        string rowToWrite = "";
        for(int i = 0; i < C; ++i){
                rowToWrite += ALPHABET[rand() % 32];
            }
        myfile << rowToWrite << "\n";
    }

    myfile.close();
    return 0;
    */

    encrypted = KEYinit((unsigned char *) argv[1]);
    cout << "Encrypted: " << encrypted;

    // read in table T
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
    Sub1Vector.push_back(pair<Key,set<int>>(KEYinit((unsigned char *) zeroString.c_str()), tempElement));

    int tal = 2;
    for (int i = 0; i < N/2 -tal; ++i) {
        vector<pair<Key,set<int>>> temp1;
        for (vector<pair<Key,set<int>>>::iterator it = Sub1Vector.begin(); it != Sub1Vector.end(); ++it){
            pair<Key,set<int>> tempPair = AddToSubsetSum(*it, T[i] ,i);
            temp1.push_back(tempPair);

        }
        for (vector<pair<Key,set<int>>>::iterator it = temp1.begin(); it != temp1.end(); ++it){
            Sub1Vector.push_back(*it);
        }
    }



    vector<string> result;

    multimap<Key, set<int>> Sub1;
    Sub1.insert(Sub1Vector.begin(), Sub1Vector.end());
    Sub1Vector.clear();
    cout << "Half way there." << endl;


    auto foundValues = Sub1.equal_range(encrypted);
    for (auto i = foundValues.first; i != foundValues.second; ++i) {
        result.push_back(getDecryptedWord(i->second));
    }

    string combinationString = "";
    for (int i = 0; i < C-1; ++i) {
        combinationString += "a";
    }
    combinationString += "b";

    Key rowCombination = KEYinit((unsigned char*) combinationString.c_str());
    for (int i = 0; i < pow(2.0,N/2+(N%2)+tal)-1; ++i) {
        Key subsetSum = KEYsubsetsum(rowCombination,T);
        foundValues = Sub1.equal_range(encrypted-subsetSum);
        set<int> rowSet = getRowSet(rowCombination);
        for (auto i = foundValues.first; i != foundValues.second; ++i) {
            set<int> tempSet = i->second;
            tempSet.insert(rowSet.begin(),rowSet.end());
            result.push_back(getDecryptedWord(tempSet));
        }
        ++rowCombination;
    }




    cout << "Found possible passwords:" << endl;
    for(int i =0; i < result.size();++i){
        cout << result[i] << endl;
    }
    return 0;
}
