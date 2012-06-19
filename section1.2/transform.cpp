/*
SECTION: 1.2
NUMBER: 2
ID: voxsim2
PROG: transform
LANG: C++
*/

/*
List of possible transformations:
    #1: 90 Degree Rotation: The pattern was rotated clockwise 90 degrees.
    #2: 180 Degree Rotation: The pattern was rotated clockwise 180 degrees.
    #3: 270 Degree Rotation: The pattern was rotated clockwise 270 degrees.
    #4: Reflection: The pattern was reflected horizontally (turned into a mirror image of itself by reflecting around a vertical line in the middle of the image).
    #5: Combination: The pattern was reflected horizontally and then subjected to one of the rotations (#1-#3).
    #6: No Change: The original pattern was not changed.
    #7: Invalid Transformation: The new pattern was not obtained by any of the above methods.

	#1: (y,x) -> (x, N-y-1) 
	00 01 02	20 10 00
	10 11 12	21 11 01
	20 21 22	22 12 02

	#2: (y,x) -> (N-y-1, N-x-1)
	00 01 02	22 21 20
	10 11 12	12 11 10
	20 21 22	02 01 00

	#3: (y,x) -> (N-x-1,y)
	00 01 02	02 12 22
	10 11 12	01 11 21
	20 21 22	00 10 20

	#4: (y,x) -> (y, N-x-1)
	00 01 02	02 01 00
	10 11 12	12 11 10
	20 21 22	22 21 20

	#5 - #1: (y,x) -> (y, N-x-1) -> (x,y)
	#5 - #2: (y,x) -> (y, N-x-1) -> (N-y-1,x)
	#5 - #3: (y,x) -> (y, N-x-1) -> (N-x-1, N-y-1)
	#6 : (y,x) -> (y,x)
*/

#include <iostream>
#include <fstream>
#include <list>
#include <map>

using namespace std;

#define G90			0
#define G180 		1
#define G270 		2
#define REFLECTION 	3
#define COMBO_1 	4
#define COMBO_2 	5
#define COMBO_3 	6
#define NO_CHANGE 	7

int main() {
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");
	int n;

	int t_values[] = {G90, G180, G270, REFLECTION, COMBO_1, COMBO_2, COMBO_3, NO_CHANGE};
	list<int> ts (t_values, t_values + sizeof(t_values) / sizeof(int));

	map<int,int> tm;
	tm[G90] = 1;
	tm[G180] = 2;
	tm[G270] = 3;
	tm[REFLECTION] = 4;
	tm[COMBO_1] = 5;
	tm[COMBO_2] = 5;
	tm[COMBO_3] = 5;
	tm[NO_CHANGE] = 6;

	fin >> n;

	char input[n][n];
	char output[n][n];

	for(int i=0; i<n*n; i++) {
		fin >> input[i/n][i%n];
	}
	for(int i=0; i<n*n; i++) {
		fin >> output[i/n][i%n];
	}

	int x;
	int y;
	for(int i=0; i<n*n; i++) {
		if(ts.size() <= 1) {
			break;
		}

		int y = i/n;
		int x = i%n;

		if(input[y][x] != output[x][n-y-1]) {
			ts.remove(G90);
		}
		if(input[y][x] != output[n-y-1][n-x-1]) {
			ts.remove(G180);
		}
		if(input[y][x] != output[n-x-1][y]) {
			ts.remove(G270);
		}
		if(input[y][x] != output[y][n-x-1]) {
			ts.remove(REFLECTION);
		}
		if(input[y][x] != output[x][y]) {
			ts.remove(COMBO_1);
		}
		if(input[y][x] != output[n-y-1][x]) {
			ts.remove(COMBO_2);
		}
		if(input[y][x] != output[n-x-1][n-y-1]) {
			ts.remove(COMBO_3);
		}
		if(input[y][x] != output[y][x]){
			ts.remove(NO_CHANGE);
		}
	}

	if(ts.size() == 0) {
		cout << 7 << endl;
		fout << 7 << endl;
	} else {
		int type = *ts.begin();

		cout << tm[type] << endl;
		fout << tm[type] << endl;
	}

	return 0;
}
