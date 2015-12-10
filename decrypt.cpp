//
// Created by Daniel Persson Proos on 2015-12-09.
//

#include <iostream>
#include <chrono>
#include <map>
#include <vector>
#include "Key.h"

using namespace std;

pair<Key,vector<vector<int>>> AddToSubsetSum(const pair<Key,vector<vector<int>>> L, Key addedValue, int index) {
    L.first = L.first + addedValue;
    for (auto i : L.second) {
        i.push_back(index);
    }

   return L;

}

int main(int argc, char* argv[]) {
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

    int n = N;
    multimap<Key, vector<int>> L;

    vector<int> tempElement;
    L.insert(pair<Key,vector<int>>(KEYinit(0), tempElement));
    for (int i = 0; i < N; ++i) {
        for (auto it : L){
            pair<Key,vector<vector<int>>> tempPair = AddToSubsetSum(it, T[i] ,i);
            L.insert(tempPair);
        }
    }
}
