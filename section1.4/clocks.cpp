/*
SECTION: 1.4
NUMBER: 3
ID: voxsim2
PROG: clocks
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

unsigned int idx[9][5] = {{0, 1, 3, 4, 9},
                          {0, 1, 2, 9, 9},
                          {1, 2, 4, 5, 9},
                          {0, 3, 6, 9, 9},
                          {1, 3, 4, 5, 7},
                          {2, 5, 8, 9, 9},
                          {3, 4, 6, 7, 9},
                          {6, 7, 8, 9, 9},
                          {4, 5, 7, 8, 9}};

unsigned int move[9];
unsigned int bestmove[9];
unsigned int nbestmove = 28;

unsigned int checkBit(unsigned int number, unsigned int x) {
    return number & (1 << x);
}
                          
unsigned int setBit(unsigned int number, unsigned int x) {
    number |= 1 << x;
    return number;
}

unsigned int toggleBit(unsigned int number, unsigned int x) {
    number ^= 1 << x;
    return number;
}

unsigned int process(unsigned int number, unsigned int m) {
    //for(unsigned int i=0; i<9; i++)
    //    cout << move[i] << " ";
    //cout << " => " << number << "\n";

    if(number == 262143) {
        unsigned int n = 0;
        for(unsigned int i=0; i<9; i++)
            n += move[i];

        if(n < nbestmove) {
            nbestmove = n;
            for(unsigned int i=0; i<9; i++)
                bestmove[i] = move[i];
        }

        return 1;
    }

    if(m == 9) {
        return 0;
    }

    unsigned int new_number;

    for(unsigned int k=0; k<=3; k++) {
        move[m] = k;
        new_number = number;

        for(unsigned int j=0; j<k; j++) {
            for(unsigned int i=0; i<5; i++) {
                if(idx[m][i] == 9)
                    continue;

                if(checkBit(new_number, idx[m][i]*2)) {
                    new_number = toggleBit(new_number, idx[m][i]*2+1);
                }
                new_number = toggleBit(new_number, idx[m][i]*2);
            }
        }
        
        /*unsigned int res = process(new_number, m+1);
        if(res == 1) 
            return 1;*/
        process(new_number, m+1);
    }
    move[m] = 0;

    return 0;
}

int main() {
    ofstream fout ("clocks.out");
    ifstream fin ("clocks.in");

    unsigned int val;
    unsigned int number = 0;

    for(unsigned int i=0; i<9; i++) {
        fin >> val;
        val /= 3;
        if((val-1)/2 == 1)
            number = setBit(number, i*2+1);
        if((val-1)%2 == 1)
            number = setBit(number, i*2);
    }
    
    cout << number << "\n";

    process(number, 0);

    for(unsigned int first=1, i=0; i<9; i++) {
        for(unsigned int j=0; j<bestmove[i]; j++) {
            if(!first)
                fout << " ";
            fout << i+1;
            first = 0;
        }
    }
    fout << "\n";

	return 0;
}
