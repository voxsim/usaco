/*
SECTION: 1.3
NUMBER: 3
ID: voxsim2
PROG: calfflac
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
 
using namespace std;

#define DEBUG	0
#define dout	if(DEBUG) cout 

string largest_palindrome;
string phrase;
int l;

int is_letter(char a) {
	return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z');
}

int next_letter(int i){
	while(i < phrase.size() && !is_letter(phrase[i])) {
		i++;
	}
	if(i >= phrase.size()) {
		return -1;
	} 
	return i;
}

int previous_letter(int i){
	while(i >= 0 && !is_letter(phrase[i])) {
		i--;
	}
	if(i < 0) {
		return -1;
	} 
	return i;
}

int equal(char a, char b) {
	return a == b || a - 32 == b || a == b - 32;
}

void find_palindrome(int d, int e, int ll) {
	int lgd = -1;
	int lge = -1;
	while(d != -1 && e != -1 && equal(phrase[d], phrase[e])) {
		ll += 2;
		lgd = d;
		lge = e;
		d = previous_letter(d-1);
		e = next_letter(e+1);
	}

	if(lge != -1 && lgd != -1 && ll > l) {
		largest_palindrome = phrase.substr(lgd, lge-lgd+1);
		l = ll;
	}
}

int main() {
	largest_palindrome = "";
	l = 0;

    ofstream fout ("calfflac.out");
    ifstream fin ("calfflac.in");

	string line;
	while (getline(fin, line))
	{
		phrase += line + '\n';
	}

	int a, b, c;
	for(int i=0;  i < phrase.size(); i++) {
		int start = -1;
		if(!is_letter(phrase[i])) {
			start -= 1;
		}
		find_palindrome(i, i+1, start);
		find_palindrome(i, i, start);	
	}
	fout << l << endl;
	fout << largest_palindrome << endl;

	return 0;
}
