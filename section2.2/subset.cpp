/*
SECTION: 2.2
NUMBER: 2
ID: voxsim2
PROG: subset
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

unsigned int N;
unsigned int subsets[40][781]; /* Matrix number x sum : n* of subset */

int main() {
    ifstream fin ("subset.in");
    ofstream fout ("subset.out");
	
    fin >> N;

    cout << N << " " << N*(N-1)/2 << endl;

    if((N*(N+1)/2) % 2 != 0) {
        fout << 0 << endl;
        return 0;
    }
    
    subsets[1][1] = 1;

    for(int i=2; i<=N; i++) {
        subsets[i][i] += 1; /* subset of only one element */
        for(int j=0; j<(i-1)*i/2; j++) {
            subsets[i][j] += subsets[i-1][j]; /* old subsets */
            subsets[i][j+i] += subsets[i-1][j]; /* old subset plus new element i */
        }
    }

    /* 
     * To have two equal subset would mean we want the number of group of N
     * elements with sum N*(N+1)/4 
     */
    fout << subsets[N][N*(N+1)/4] << endl;
    return 0;
}
