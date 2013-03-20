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
#include <list>

using namespace std;

#define BLUE	0
#define RED		1
#define NOCOLOR	-1

struct cut_point {
    int blue;
    int red;
} cut_point;

int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");
	int n;
	string beads;
	list<cut_point> cut_points;
	int color =	NOCOLOR;
	int count = 0;
	int max = 0;

	fin >> n;
	fin >> beads;


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
        }
		if(beads[i] == 'r' && color == NOCOLOR) {
			count += 1;
			color = RED;
        }

        //Here we have a cut point red to blue
		if(beads[i] == 'b' && color == RED) {
            // Get the last and set the red part
            if(cut_points.size() > 0) {
                cut_point cp = cut_points.pop_back();
                cp.red = count;
                if(cp.red + cp.blue > max) {
                    max = cp.red + cp.blue;
                }

                cut_points.push_back(cp);
            }
            cut_point cp = new cut_point();
            cp.red = count;
            cp.blue = 1;
            cut_points.push_back(cp);
			count = 1;
			color = BLUE;
        }

        //Here we have a cut point blue to red
		if(beads[i] == 'r' && color == BLUE) {
            // Get the last and set the blue part
            if(cut_points.size() > 0) {
                cut_point cp = cut_points.pop_back();
                cp.blue = count;
                if(cp.red + cp.blue > max) {
                    max = cp.red + cp.blue;
                }

                cut_points.push_back(cp);
            }
            cut_point cp = new cut_point();
            cp.blue = count;
            cp.red = 1;
            cut_points.push_back(cp);
			count = 1;
			color = RED;
        }
	}
	
    list<string>::iterator it;
	for(it = cut_points.begin(); it != cut_points.end(); it++)
		fout << (*it).blue << " " << (*it).red << endl;

	cout << max << endl;

	return 0;
}
