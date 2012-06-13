/*
SECTION: 1.1
NUMBER: 4
ID: voxsim2
PROG: beads
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define BLUE	0
#define RED		1
#define NOCOLOR	-1

int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");
	int n;
	string beads;
	int first_bead = NOCOLOR;
	int first_group = -1;

	fin >> n;
	fin >> beads;

	int color =	NOCOLOR;
	int count = 0;
	int old_count = 0;
	int max = 0;
	int change = 0;
	for(int i=0; i<n; i++) {
		if(beads[i] == 'w') {
			count += 1;	
		}
		if(beads[i] == 'b' && color == BLUE) {
			count += 1;
        }
		if(beads[i] == 'r' && color == RED) {
			count += 1;
        }
		if(beads[i] == 'b' && color == NOCOLOR) {
			count += 1;
			color = BLUE;
			first_bead = BLUE;
        }
		if(beads[i] == 'r' && color == NOCOLOR) {
			count += 1;
			color = RED;
			first_bead = RED;
        }
		if(beads[i] == 'b' && color == RED) {
			if(first_group == -1) {
				first_group = count;
			}
			if(old_count + count > max) {
				max = old_count + count;
			}
			old_count = count;
			count = 1;
			color = BLUE;
			change = 1;	
        }
		if(beads[i] == 'r' && color == BLUE) {
			if(first_group == -1) {
				first_group = count;
			}
			if(old_count + count > max) {
				max = old_count + count;
			}
			old_count = count;
			count = 1;
			color = RED;
			change = 1;
        }
	}

	if(old_count + count > max) {
		max = old_count + count;
	}

	if(change == 0){
        max = count;
    } else {
		old_count = 0;
		color = first_bead;
		count = first_group;

		cout << max << endl;
		cout << first_group << endl;
		cout << color << endl;
		cout << count << endl;

		int stop = 0;
		for(int i=n; i>first_group; i--) {
			cout << i << endl;
			if(beads[i] == 'w') {
				count += 1;	
			}
			if(beads[i] == 'b' && color == BLUE) {
				count += 1;
			}
			if(beads[i] == 'r' && color == RED) {
				count += 1;
			}
			if(beads[i] == 'b' && color == RED) {
				if(old_count + count > max) {
					max = old_count + count;
				}
				old_count = count;
				count = 1;
				color = BLUE;
				if(stop == 1) {
					break;
				}
				stop = 1;
			}
			if(beads[i] == 'r' && color == BLUE) {
				if(old_count + count > max) {
					max = old_count + count;
				}
				old_count = count;
				count = 1;
				color = RED;
				if(stop == 1) {
					break;
				}
				stop = 1;
			}
//			cout << color << " " << count << endl;
		}

		if(old_count + count > max) {
			max = old_count + count;
    	}
	}

	cout << max << endl;
	fout << max << endl;

	return 0;
}
