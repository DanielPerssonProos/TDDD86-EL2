#include <chrono>
#include <map>
#include <unordered_set>
#include "Key.h"
#include <vector>
#include <thread>

using namespace std;

pair<Key,unordered_set<int>> AddToSubsetSum(pair<Key,unordered_set<int>> L, Key addedValue, int index) {
    cout << "First:  " << L.first << endl;
    cout << "second: " << addedValue << endl;
    L.first = L.first + addedValue;
    cout << "After:  " << L.first << endl;
    L.second.insert(index);
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

    multimap<Key, unordered_set<int>> Sub1;

    unordered_set<int> tempElement;
    Sub1.insert(pair<Key,unordered_set<int>>(KEYinit((unsigned char *) "aaaaa"), tempElement));

    multimap<Key, unordered_set<int>> temp1;


    for (int i = 0; i < N/2; ++i) {
        for (auto it : Sub1){
            //std::this_thread::sleep_for (std::chrono::seconds(1));
            pair<Key,unordered_set<int>> tempPair = AddToSubsetSum(it, T[i] ,i);
            temp1.insert(tempPair);
            }

        for(auto a : temp1){
            Sub1.insert(a);
        }
    }

    vector<pair<Key,vector<int>>> result;

    multimap<Key, unordered_set<int>> Sub2;

    unordered_set<int> tempElement;
    Sub1.insert(pair<Key,unordered_set<int>>(KEYinit((unsigned char *) "aaaaa"), tempElement));

    multimap<Key, unordered_set<int>> temp2;
    for (int i = N/2; i < N; ++i) {
        for (auto it : Sub2){
            //std::this_thread::sleep_for (std::chrono::seconds(1));
            pair<Key,unordered_set<int>> tempPair = AddToSubsetSum(it, T[i] ,i);
            temp2.insert(tempPair);
            }

        for(auto a : temp2){
            if (Sub1.find(encrypted-a.first)!= Sub1.end()) {
                result.push_back(a);
            }
            Sub2.insert(a);
        }
    }

    /*
    vector<string> foundDecryptions;
    pair<multimap<Key,unordered_set<int>>::iterator,multimap<Key,unordered_set<int>>::iterator> ret;
    ret = Sub1.equal_range(encrypted);

    cout << Sub1.size() << endl;

*/
    for (auto itr =ret.first; itr!=ret.second; ++itr){
        cout << "Found matching key" << endl;
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
