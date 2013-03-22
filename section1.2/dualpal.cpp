/*
SECTION: 1.2
NUMBER: 5
ID: voxsim2
PROG: dualpal
LANG: C++
COMPLEXITY: O(m * 10 * len(number))
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string to_base(int number, int b) {
	stringstream ss;

	while(number > 1) {
		int div = number/b;
		int rest = number%b;
		ss << rest;
		number = div; 
	}

	if(number == 1) {
		ss << 1;
	}

	return ss.str();
}

int is_palindromic(string str) {
	int is_pal = 1;
	for(int i=0; i<str.size()/2; i++) {
		if(str[i] != str[str.size()-1-i]) {
			is_pal = 0;
			break;
		}
	}
	return is_pal;
}

int main() {
    ofstream fout ("dualpal.out");
    ifstream fin ("dualpal.in");

	int n;
	int s;

	fin >> n >> s;

	int count = 0;
	int i = s+1;
	while(count < n) { // O(m) where m >= n 
		int ok = 0;
		for(int b=2; b<11 && ok<2; b++) { //O(10)
			string number = to_base(i, b);
			if(is_palindromic(number)) { //O(Len(number))
				ok += 1;
				if(ok == 2) {
					cout << i << endl;
					fout << i << endl;
					count++;
				}
			}
		}
		i++;
	}

	return 0;
}
