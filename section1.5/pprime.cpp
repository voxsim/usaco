/*
SECTION: 1.5
NUMBER: 2 
ID: voxsim2
PROG: pprime
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>

using namespace std;

unsigned int a;
unsigned int b;

bool isPrime(unsigned int palindrome) {
    bool isPrime = true;
    for(unsigned int j=2; j<=sqrt(palindrome) && isPrime; j++) {
        isPrime = (palindrome%j != 0);
    }
    return isPrime;
}

int main() {
    ofstream fout ("pprime.out");
    ifstream fin ("pprime.in");
	
    priority_queue<int, vector<int>, greater<int> > pprime;

    fin >> a >> b;
    cout << a << " " << b << endl;

    if(b == 100000000) 
        b =  99999999;

    unsigned int palindrome;
    /* generate five digit palindrome: */
    for (unsigned int d1 = 1; d1 <= 9; d1+=2) {	/* only odd; evens aren't so prime */
        palindrome = d1;
        if(palindrome >= a && palindrome <= b && isPrime(palindrome)) {
            pprime.push(palindrome);  
        }
        if(d1 == 1 && 11 >= a && 11 <= b) {
            pprime.push(11);  
        }
        for (unsigned int d2 = 0; d2 <= 9; d2++) {
            palindrome = 100*d1 + 10*d2 + d1;
            if(palindrome >= a && palindrome <= b && isPrime(palindrome)) {
                pprime.push(palindrome);  
            }
            palindrome = 1000*d1 + 100*d2 + 10*d2 + d1;
            if(palindrome >= a && palindrome <= b && isPrime(palindrome)) {
                pprime.push(palindrome);  
            }
            for (unsigned int d3 = 0; d3 <= 9; d3++) {
                palindrome = 10000*d1 + 1000*d2 +100*d3 + 10*d2 + d1;
                if(palindrome >= a && palindrome <= b && isPrime(palindrome)) {
                    pprime.push(palindrome);  
                }
                palindrome = 100000*d1 + 10000*d2 + 1000*d3 +100*d3 + 10*d2 + d1;
                if(palindrome >= a && palindrome <= b && isPrime(palindrome)) {
                    pprime.push(palindrome);  
                }
                for (unsigned int d4 = 0; d4 <= 9; d4++) {
                    palindrome = 1000000*d1 + 100000*d2 + 10000*d3 + 1000*d4 +100*d3 + 10*d2 + d1;
                    if(palindrome >= a && palindrome <= b && isPrime(palindrome)) {
                        pprime.push(palindrome);
                    }
                    palindrome = 10000000*d1 + 1000000*d2 + 100000*d3 + 10000*d4 + 1000*d4 +100*d3 + 10*d2 + d1;
                    if(palindrome >= a && palindrome <= b && isPrime(palindrome)) {
                        pprime.push(palindrome);
                    }
                }
            }
        }
    }
	
    while(!pprime.empty()){
		fout << pprime.top() << endl;
		cout << pprime.top() << endl;
		pprime.pop();
	}

    return 0;
}
