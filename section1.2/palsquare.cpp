/*
SECTION: 1.2
NUMBER: 4
ID: voxsim2
PROG: palsquare
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

string to_base(int number, int b) {
	stringstream ss;

	while(number > 1) {
		int div = number/b;
		int rest = number%b;
//		cout << number << " " << div << " " << rest << endl;

		if(rest > 9) {
			char c = ((rest - 10) + 'A');
			ss << c;
		} else {
			ss << rest;
		}

		number = div; 
	}

	if(number == 1) {
		ss << 1;
	}

	string rev = ss.str();
	reverse(rev.begin(), rev.end());
	return rev;
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
    ofstream fout ("palsquare.out");
    ifstream fin ("palsquare.in");

	int n = 300;
	int b;

	fin >> b;

	for(int i=1; i<n; i++) {
		string number = to_base(i*i, b);
		if(is_palindromic(number)) {
			cout << to_base(i, b) << " " << number << endl;
			fout << to_base(i, b) << " " << number << endl;
		}
	}

	return 0;
}
