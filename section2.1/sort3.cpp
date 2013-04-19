/*
SECTION: 2.1
NUMBER: 3
ID: voxsim2
PROG: sort3
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

unsigned int N;
unsigned int numbers[1000];
unsigned int n_one;
unsigned int n_two;
unsigned int misplaced[3][3];

int main() {
    ifstream fin ("sort3.in");
    ofstream fout ("sort3.out");
	
    fin >> N;
    
    for(unsigned int i=0; i<N; i++) {
        fin >> numbers[i];
        if(numbers[i] == 1) {
            n_one++;
        }
        if(numbers[i] == 2) {
            n_two++;
        }
    }

    // We create a matrix j instead of i
    unsigned int should_be;
    for(unsigned int i=0; i<N; i++) {
        if(i < n_one)
            should_be = 0;
        if(i < n_one + n_two && i >= n_one)
            should_be = 1;
        if(i >= n_one + n_two)
            should_be = 2;

        misplaced[numbers[i]-1][should_be]++;
    }

    for(unsigned int j=0; j<3; j++) {
        for(unsigned int k=0; k<3; k++) {
            cout << misplaced[j][k] << " ";
        }
        cout << endl;
    }

    // We calculate the minimal for each j instead of k -> one change
    unsigned int c0_1 = min(misplaced[0][1], misplaced[1][0]);
    unsigned int changes = c0_1;
    changes += min(misplaced[0][2], misplaced[2][0]);
    changes += min(misplaced[1][2], misplaced[2][1]);
    // We calculate the maximal minus the minimal for each j instead of k -> two changes (2 instead of 3, 3 instead of 1)
    changes += (max(misplaced[0][1], misplaced[1][0]) - c0_1)*2;
    fout << changes << endl;
    return 0;
}
