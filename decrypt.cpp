//
// Created by Daniel Persson Proos on 2015-12-09.
//

#include <iostream>
#include <chrono>
#include <map>
#include <unordered_set>
#include "Key.h"
#include <vector>

using namespace std;

pair<Key,unordered_set<int>> AddToSubsetSum(pair<Key,unordered_set<int>> L, Key addedValue, int index) {
    L.first = L.first + addedValue;
    L.second.insert(index);
    cout << "I bet u dont reach thisd";

   return L;

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

    // read in table T
    for (int i = 0; i < N; ++i) {
        scanf("%s", buffer);
        T[i] = KEYinit(buffer);
    }

    auto begin = chrono::high_resolution_clock::now();

    multimap<Key, unordered_set<int>> L;

    unordered_set<int> tempElement;
    L.insert(pair<Key,unordered_set<int>>(KEYinit(0), tempElement));
    for (int i = 0; i < N; ++i) {
        for (auto it : L){
            cout << "Here";
            pair<Key,unordered_set<int>> tempPair = AddToSubsetSum(it, T[i] ,i);
            if(tempPair.first <= encrypted){
                L.insert(tempPair);
            }
        }
    }
    vector<string> foundDecryptions;
    pair<multimap<Key,unordered_set<int>>::iterator,multimap<Key,unordered_set<int>>::iterator> ret;
    ret = L.equal_range(encrypted);



    for (auto itr =ret.first; itr!=ret.second; ++itr){
        int twoPower = 2^4;
        string decrypted = "";
        int letter = 0;
        for(int i = 0; i < N; i++){
            if (i % 5 == 0 && i != 0) {
                twoPower = 2^4;
                decrypted += ALPHABET[letter];
                letter = 0;
            }
            if (itr->second.find(i) != itr->second.end()) {
                letter += twoPower;
            }
            twoPower /= 2;

        }
        foundDecryptions.push_back(decrypted);
        decrypted = "";
    }

    cout << "Found possible passwords:" << endl;
    for(int i =0; i < foundDecryptions.size();++i){
        cout << foundDecryptions[i] << endl;
    }



}
