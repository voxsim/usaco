/*
SECTION: 1.1
NUMBER: 3
ID: voxsim2
PROG: friday
LANG: C++
SOLUTION: Loop years from 1900, for each year loop the months and add day[D]++ where D is the day of the 13th of the month.
COMPLEXITY: O(nyears * months=12) -> O(nyears)
*/

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");
	int nyears;
	int nmonths = 12;
	int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int days[] = {0, 0, 0, 0, 0, 0, 0};

	fin >> nyears;

	int count = 0;
	for(int i=0; i<nyears; i++) { // O(nyears)
		int year = 1900 + i;
		for(int j=0; j<nmonths; j++) { //O(months)
			int month = months[j];
			if(j == 1 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
			  month += 1;
			}

			days[(count+13) % 7] += 1;
			count += month;
		}
	}

	int space = 0;
	for(int i=6; i<13; i++) {
//		cout << "days " << i << ": " << days[i % 7] << endl;
		if(space == 1) 	{
			fout << " ";
		}
		fout << days[i % 7];
		space = 1;
	}
	fout << endl;

	return 0;
}
