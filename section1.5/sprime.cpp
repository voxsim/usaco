/*
SECTION: 1.5
NUMBER: 3
ID: voxsim2
PROG: sprime
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>

using namespace std;

unsigned int N;

bool isPrime(unsigned int number) {
    bool isPrime = true;
    for(unsigned int j=2; j<=sqrt(number) && isPrime; j++) {
        isPrime = (number%j != 0);
    }
    return isPrime;
}

int main() {
    ofstream fout ("sprime.out");
    ifstream fin ("sprime.in");
	
    priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int> > sprime;

    fin >> N;
    
    /* sprime of length 1 */
    sprime.push(2);
    sprime.push(3);
    sprime.push(5);
    sprime.push(7);

    unsigned int i=1;
    unsigned int j=4;
    while(i<N) {
        for(int k=1; k<=9; k++) {
            unsigned int number = sprime.top()*10 + k;
            if(isPrime(number)) {
                sprime.push(number);
            }
        }
        j--;
		sprime.pop();
        if(j==0) {
            i++;
            j=sprime.size();
        }
    }

    while(!sprime.empty()){
		fout << sprime.top() << endl;
		cout << sprime.top() << endl;
		sprime.pop();
	}

    return 0;
}
