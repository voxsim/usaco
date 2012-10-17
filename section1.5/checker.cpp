/*
SECTION: 1.5
NUMBER: 4
ID: voxsim2
PROG: checker
LANG: C++

TEXT:


Checker Challenge

Examine the 6x6 checkerboard below and note that the six checkers are arranged on the board so that one and only one is placed in each row and each column, and there is never more than one in any diagonal. (Diagonals run from southeast to northwest and southwest to northeast and include all diagonals, not just the major two.)

          Column
    1   2   3   4   5   6
  -------------------------
1 |   | O |   |   |   |   |
  -------------------------
2 |   |   |   | O |   |   |
  -------------------------
3 |   |   |   |   |   | O |
  -------------------------
4 | O |   |   |   |   |   |
  -------------------------
5 |   |   | O |   |   |   |
  -------------------------
6 |   |   |   |   | O |   |
  -------------------------

The solution shown above is described by the sequence 2 4 6 1 3 5, which gives the column positions of the checkers for each row from 1 to 6:
ROW 1   2   3   4   5   6
COLUMN  2   4   6   1   3   5

This is one solution to the checker challenge. Write a program that finds all unique solution sequences to the Checker Challenge (with ever growing values of N). Print the solutions using the column notation described above. Print the the first three solutions in numerical order, as if the checker positions form the digits of a large number, and then a line with the total number of solutions. 

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
