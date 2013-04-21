/*
SECTION: 2.1
NUMBER: 5
ID: voxsim2
PROG: hamming
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

unsigned int N;
unsigned int B;
unsigned int D;
unsigned int codewords[256];

void markNearCodewords(unsigned int number, unsigned int depth) {
    if(depth >= D - 1)
        return;


    for(unsigned int j=0; j<B; j++) {
        //Toggle j bit
        unsigned int k = number ^ 1 << j;
        //cout << "toggle: " << k << " " << depth << endl;
        codewords[k] = 1;
        markNearCodewords(k, depth+1);
    }
}

int main() {
    ifstream fin ("hamming.in");
    ofstream fout ("hamming.out");
	
    fin >> N >> B >> D;

    unsigned int founded = 0;

    for(unsigned int i=0; i<pow(2,B)&&founded<N; i++) {
        if(!codewords[i]) {
            fout << i;
            //cout << "NUMBER: " << i << endl;
            founded++;
            if(founded % 10 != 0 && founded < N) {
                fout << " ";
            }
            if(founded % 10 == 0 && founded < N) {
                fout << endl;
            }
            codewords[i] = 1;
            markNearCodewords(i, 0);
        }
    }
    fout << endl;

    return 0;
}
