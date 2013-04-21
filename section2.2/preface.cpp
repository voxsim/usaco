/*
SECTION: 2.2
NUMBER: 1
ID: voxsim2
PROG: preface
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

typedef struct {
    unsigned int n;
    char l;
} roman;

unsigned int N;
roman romans[7];
unsigned int symbols[3500][7];

void toRoman(int number, int n) {
    for(int j=6; j>=0&&n>0; j--) {
        unsigned int r = n / romans[j].n;
        if(r > 0) {
            n = n - r*romans[j].n;
            for(unsigned int i=0; i<r; i++) {
                cout << romans[j].l;
                symbols[number-1][j]++;
            }
            //cout << r << "x" << romans[j].l;
        }

        if(j>0) {
//            cout << " " << romans[j].n << " " << romans[j-1].n << " = " << n << endl;
            if(romans[j].n - romans[j-1].n == n && romans[j-1].n != n) {
                cout << romans[j-1].l << romans[j].l;
                n = n - romans[j].n + romans[j-1].n;
                symbols[number-1][j]++;
                symbols[number-1][j-1]++;
            }
        }
        if(j>1) {
//           cout << " " << romans[j].n << " " << romans[j-2].n << " = " << n << endl;
            if(romans[j].n - romans[j-2].n == n && romans[j-2].n != n) {
                cout << romans[j-2].l << romans[j].l;
                n = n - romans[j].n + romans[j-2].n;
                symbols[number-1][j]++;
                symbols[number-1][j-2]++;
            }
        }
    }
}

int main() {
    ifstream fin ("preface.in");
    ofstream fout ("preface.out");
	
    fin >> N;

    roman I;
    I.n = 1;
    I.l = 'I';
    romans[0] = I;
    roman V;
    V.n = 5;
    V.l = 'V';
    romans[1] = V;
    roman X;
    X.n = 10;
    X.l = 'X';
    romans[2] = X;
    roman L;
    L.n = 50;
    L.l = 'L';
    romans[3] = L;
    roman C;
    C.n = 100;
    C.l = 'C';
    romans[4] = C;
    roman D;
    D.n = 500;
    D.l = 'D';
    romans[5] = D;
    roman M;
    M.n = 1000;
    M.l = 'M';
    romans[6] = M;

    for(int i=0; i<N; i++) {
        if(i == 0) {
            for(int j=0; j<7; j++)
                symbols[i][j] = 0;
        } else {
            for(int j=0; j<7; j++)
                symbols[i][j] = symbols[i-1][j];
        }
        cout << "number " << i+1 << ": ";
        int number = i+1;
        if(number / 1000 > 0) {
            toRoman(i+1, number - number%1000);
            number = number%1000;
        }
        if(number / 100 > 0) {
            toRoman(i+1, number - number%100);
            number = number%100;
        }
        if(number / 10 > 0) {
            toRoman(i+1, number - number%10);
            number = number%10;
        }
        if(number > 0) {
            toRoman(i+1, number);
        }
        cout << endl;
    }

    for(int j=0; j<7&&romans[j].n<=N; j++) {
        fout << romans[j].l << " " << symbols[N-1][j] << endl;
    }

    return 0;
}
