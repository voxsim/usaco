/*
SECTION: 1.2
NUMBER: 3
ID: voxsim2
PROG: namenum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <list>

using namespace std;

int main() {
    ofstream fout ("namenum.out");
    ifstream fin ("namenum.in");
    ifstream fdict ("namenumdict.txt");
	
	string number;
	fin >> number;
	cout << "number: " << number << endl;
	
	map<string, list<string> > index;
	map<char, int> letters;
	
	for(int i=0; i<16; i++) {
		char c = 'A' + i;
		letters[c] = (i/3) + 2;
	}

	for(int i=17; i<25; i++) {
		char c = 'A' + i;
		letters[c] = ((i-1)/3) + 2;
	}

	while(!fdict.eof()) {
		string s;
		fdict >> s;
		if(!s.empty()) {
			stringstream ss;
			int notAdd = 0;
			for(int i=0; i<=s.size(); i++) {
				char c = s[i];
				if(c == 'Z' || c == 'Q') {
					notAdd = 1;
					break;
				}
				if(letters[c] != 0) {
					ss << letters[c];
				}
			}
			if(!notAdd) {
				string id = ss.str();
				cout << s << " " << id << endl;
				list<string> values = index[id];
				values.push_back(s);
				index[id] = values;
			}
		}
	}

	list<string> values = index[number];

	if(values.size() != 0) {
		for (list<string>::iterator it=values.begin(); it!=values.end(); ++it) {
    		cout << *it << endl;
			fout << *it << endl;
		}
	} else {
		cout << "NONE" << endl;
		fout << "NONE" << endl;
	}

	return 0;
}
