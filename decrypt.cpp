#include <chrono>
#include <map>
#include <set>
#include "Key.h"
#include <vector>
#include <thread>
#include <bitset>
#include <fstream>

using namespace std;


pair<Key,set<int>> AddToSubsetSum(const pair<Key,set<int>>& L, Key& addedValue, int index) {
    set<int> returnedSet = L.second;
    returnedSet.insert(index);
    return pair<Key,set<int>>(L.first + addedValue,returnedSet);

}

string getDecryptedWord(Key key, set<int> rows) {
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


    for (int i = 0; i < 24; ++i) {
        cout << "<<New iteration>>" << endl;
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
    cout << "First part done." << endl;

    multimap<Key, set<int>> Sub2;
    set<int> tempElement2;
    Sub2.insert(pair<Key,set<int>>(KEYinit((unsigned char *) zeroString.c_str()), tempElement2));


    auto foundValues = Sub1.equal_range(encrypted);
    for (auto i = foundValues.first; i != foundValues.second; ++i) {
        result.push_back(getDecryptedWord(i->first,i->second));
    }

    multimap<Key, set<int>> temp2;
    for (int i = 20; i < N; ++i) {
        for (auto it : Sub2){
            pair<Key,set<int>> tempPair = AddToSubsetSum(it, T[i] ,i);
            temp2.insert(tempPair);
            }

        for(auto a : temp2){
            foundValues = Sub1.equal_range(encrypted-a.first);
            for (auto i = foundValues.first; i != foundValues.second; ++i) {
                set<int> tempSet = a.second;
                tempSet.insert(i->second.begin(), i->second.end());
                result.push_back(getDecryptedWord(i->first,tempSet));
                cout << "Rows: ";
                bool firstIteration = true;
                for (int row : tempSet) {
                    if (!firstIteration) {
                        cout << ",";
                    } else {
                        firstIteration = false;
                    }
                    cout << row;
                }
                cout << endl;
                cout << "Unencrypted word: " << getDecryptedWord(KEYinit((unsigned char *) zeroString.c_str()),tempSet) << endl;
                cout << "Sub1 part: "<< i->first << endl;
                cout << "Sub2 part: "<< a.first << endl;
                cout << "Encrypted: "<< encrypted << endl << endl;
                tempSet.clear();
            }


            Sub2.insert(a);
        }
        temp2.clear();
    }
    cout << "Sub2: " << Sub2.size() << endl;




    cout << "Found possible passwords:" << endl;
    for(int i =0; i < result.size();++i){
        cout << result[i] << endl;
    }
    return 0;
}
