/*
SECTION: 1.5
NUMBER: 3
ID: voxsim2
PROG: numtri
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

/*
 * Albero binario completo:
 * radice i e figli in 2i e 2i+1 (partendo da 1)
 * Altezza massima R: 1000
 * numero massimo 500*1001 = 500500
*/

/*
 * radice i e figli 2i e 2i+1
 *
 * 1 -> 2,3
 * 2 -> 4,5
 * 3 -> 6,7
 * 4 -> 8,9
 * 5 -> 10,11
 * 6 -> 12,13
 * 7 -> 14,15
 *
 * radice i e figli 2i-l e 2i+1-l (l indice di quanto sei a destra, inizia da 0)
 *
 * i=1, h=0, l=0 -> 2,3
 * i=2, h=0, l=0 -> 4,5
 * i=3, h=0, l=1 -> 5,6
 * i=4, h=1, l=0 -> 7,8
 * i=5, h=1, l=1 -> 8,9
 * i=6, h=1, l=2 -> 9,10
 * i=7, h=2, l=1 -> 11,12
 *
 * */

unsigned int n;
unsigned int values[500500];

int main() {
    ofstream fout ("numtri.out");
    ifstream fin ("numtri.in");

    fin >> n;

    for(unsigned int i=0; i<((n*(n+1))/2); i++) {
        fin >> values[i];
        cout << "pos: " << i+1 << " => val: " << values[i] << "\n";
    }

    return 0;
}
