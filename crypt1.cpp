/*
SECTION: 1.3
NUMBER: 4
ID: voxsim2
PROG: crypt1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int numbers[9];

int is_in_number_array(int n, int c) {
	while(n > 0){
		int rest = n%10;
		n /= 10;
	
		int ok=0;
		for(int i=0; i<c && !ok; i++) {
			if(numbers[i] == rest) {
				ok = 1;
			}
		}
		if(!ok) {
			return 0;
		}
	}
	return 1;
}

int main() {
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");

	int n;
	int m = 5;
	fin >> n;
	
	int numb[n];

	for(int i=0; i<n; i++) {
		fin >> numbers[i];
	}
	
	for(int i=0; i<m; i++) {
		numb[i] = 0;
	}

	int p = pow(n, 5);
	
	int count = 0;
	for(int i=0; i<p; i++) {
		if(i > 0) {
			int l=m-1;
			do {
				numb[l] += 1;
				if(numb[l] >= n) {
					numb[l] = 0;
					numb[l-1] += 1; 
				}
				l = l-1;
			} while(numb[l] >= n);
		}

		int a = numbers[numb[0]]*100 + numbers[numb[1]]*10 + numbers[numb[2]];
		int b = numbers[numb[3]]*10; 
		int c = numbers[numb[4]];

		int psum1 = a*c;

		if(!(psum1 < 1000 && is_in_number_array(psum1, n))) {
			continue;
		}

		int psum2 = a*b;

		if(!(psum2/10 < 1000 && is_in_number_array(psum2/10, n))) {
			continue;
		}

		int sum = psum1 + psum2;

		if(!(sum < 10000 && is_in_number_array(sum, n))) {	
			continue;
		}

		count += 1;
	}

	fout << count << endl;

	return 0;
}
