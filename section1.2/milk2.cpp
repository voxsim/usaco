/*
SECTION: 1.2
NUMBER: 1
ID: voxsim2
PROG: milk2
LANG: C++
*/
#include <iostream>
#include <fstream>

#define TIME_TOTAL 1000000
#define IDLE 0
#define MILK 1

using namespace std;

int times[TIME_TOTAL];

int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");
	int n;
	int first_time;
	int last_time;
	int max_last_time = 0;
	int min_first_time = TIME_TOTAL;

//	for(int i=0; i<TIME_TOTAL; i++) {
//		times[i] = 0;
//	}

	fin >> n;

	for(int i=0; i<n; i++) {
		fin >> first_time >> last_time;

		if(first_time < min_first_time) {
			min_first_time = first_time;
		}

		if(last_time > max_last_time) {
			max_last_time = last_time;
		}

		for(int j=first_time; j<last_time; j++) {
			times[j] = 1;
		}
	}

	int time_milking = 0;
	int idle_time = 0;
	int count_0 = 0;
	int count_1 = 0;
	int type = MILK;
	for(int i=min_first_time; i<max_last_time; i++) {
		if(times[i] == 0 && type == MILK) {
			type = IDLE;
			if(time_milking < count_1) {
				time_milking = count_1;
			}
			count_1 = 0;
		}
		if(times[i] == 1 && type == IDLE) {
			type = MILK;
			if(idle_time < count_0) {
				idle_time = count_0;
			}
			count_0 = 0;
		}
		if(times[i] == 0 && type == IDLE) {
			count_0 += 1;
		}
		if(times[i] == 1 && type == MILK) {
			count_1 += 1;
		}
	}

	if(time_milking < count_1) {
		time_milking = count_1;
    }

	cout << time_milking << " " << idle_time << endl;
	fout << time_milking << " " << idle_time << endl;

	return 0;
}
