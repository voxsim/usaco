/*
SECTION: 1.1
NUMBER: 2
ID: voxsim2
PROG: gift1
LANG: C++
SOLUTION: Create a map of <person, money>, initially setted all values to 0 and so on..
COMPLEXITY = O(NP + NP*number_people) -> O(NP^2)
*/

//TODO: Loop keys of the map C++

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

int main() {
	ofstream fout ("gift1.out");
	ifstream fin ("gift1.in");

	list<string> nps;
	map<string, int> frs;
	int np;
	string fr;
	string gifter;
	int initial_amount; 
	int number_people;

	fin >> np;

	for(int i=0; i<np; i++) { //O(NP)
		fin >> fr;
//		cout << fr << endl;
		frs[fr] = 0;
		nps.push_back(fr);
	}

	for(int i=0; i<np; i++) { //O(NP * number_people)
		fin >> fr;
//		cout << fr << endl;
		fin >> initial_amount >> number_people;
//		cout << initial_amount << " " << number_people << endl;
		int gift = 0;
		if(initial_amount > 0) {
			gift = initial_amount/number_people;
		}
		frs[fr] -= initial_amount;
		for(int j=0; j<number_people; j++) {
			fin >> gifter;
			frs[gifter] += gift;
		}
		if(number_people != 0) {
			frs[fr] += initial_amount % number_people;
		}
	}

	list<string>::iterator it;
	for(it = nps.begin(); it != nps.end(); it++)
		fout << *it << " " << frs[*it] << endl;

//	map<string, int>::iterator it;
//	for(it = frs.begin(); it != frs.end(); it++)
//		fout << (*it).first << " => " << (*it).second << endl;
    return 0;
}
