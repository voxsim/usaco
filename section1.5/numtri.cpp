/*
SECTION: 1.5
NUMBER: 1
ID: voxsim2
PROG: numtri
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

unsigned int R;
unsigned int values[1000][1000];

unsigned int max(unsigned int a, unsigned int b) {
    return a > b ? a : b;
}

int main() {
    ofstream fout ("numtri.out");
    ifstream fin ("numtri.in");

    fin >> R;

    for(unsigned int i=0; i<R; i++) {
        for(unsigned int j=0; j<i+1; j++) {
            fin >> values[i][j];
        }
    }
        
    for(int i=R-2; i>-1; i--) {
        for(unsigned int j=0; j<i+1; j++) {
            values[i][j] += max(values[i+1][j], values[i+1][j+1]);
        }
    }

    fout << values[0][0] << endl;
    return 0;
}
