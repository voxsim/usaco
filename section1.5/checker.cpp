/*
SECTION: 1.5
NUMBER: 4
ID: voxsim2
PROG: checker
LANG: C++
*/
/*
Solution: DFS with memoization, check the status in col, diagonal left and digonal right.
Complexity: ??
*/

#include <iostream>
#include <fstream>
#define MAX_N 13

using namespace std;

unsigned int n;
unsigned int cols[MAX_N];
unsigned int diagr[2*MAX_N-1];
unsigned int diagl[2*MAX_N-1];
unsigned int m;
unsigned int gpos[3][MAX_N];

void process_cell(unsigned int row, unsigned int col) {
    unsigned int idr = 5 + (row - col);
    unsigned int idl = row + col;

    if(cols[col] || diagr[idr] || diagl[idl]) {
        return;
    }
    
    if(row >= n) {
        return;
    }

    if(row == n-1) {
        if(m < 3)
            gpos[m][row] = col;
        
        m++;

        if(m < 3) {
            for(unsigned int i=0; i<n-1; i++) {
                gpos[m][i] = gpos[m-1][i];
            }
        }

        //cout << "ARRIVATO ALLA FINE\n";
        return;
    }

    cols[col] = 1;
    diagr[idr] = 1;
    diagl[idl] = 1;
    if(m < 3)
        gpos[m][row] = col;

    for(unsigned int i=0; i<n; i++) {
        process_cell(row+1, i);
    }

    cols[col] = 0;
    diagr[idr] = 0;
    diagl[idl] = 0;

    return;
}

int main() {
    ofstream fout ("checker.out");
    ifstream fin ("checker.in");

    fin >> n;

    unsigned int * positions = new unsigned int[n];

    for(unsigned int i=0; i<n; i++) {
        positions[i] = 0;
    }
    
    for(unsigned int col=0; col<n; col++) {
        process_cell(0, col);
    }

    unsigned int l = m < 3 ? m : 3;

    for(unsigned int i=0; i<l; i++) {
        for(unsigned int col=0; col<n; col++) {
            if(col > 0) {
                fout << " ";
            }
            fout << gpos[i][col]+1;
        }
        fout << "\n";
    }
    fout << m << "\n";

    return 0;
}
