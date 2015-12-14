//
// Created by Daniel Persson Proos on 2015-12-09.
//

#include <iostream>
#include <chrono>
#include <set>
#include "Key.h"

using namespace std;

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


    set<Key> L;
    L.insert(KEYinit(0));
    for ( int i = 0; i < N; ++i) {
        L2 = L;
        for (set<Key>::iterator j = L2.begin(); j != L2.end(); ++j) {
            *j = T[i]
        }
        L.insert()
    }
}