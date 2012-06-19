/*
SECTION: 1.3
NUMBER: 1
ID: voxsim2
PROG: milk
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct Farmer {
    int p;
    int a;
};

class ComparePrice {
public:
    bool operator()(Farmer& f1, Farmer& f2)
    {
		if(f1.p > f2.p) return true;
		return false;
    }
};


int main() {
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");

	priority_queue<Farmer, vector<Farmer>, ComparePrice> farmers;
	int n, m, a, p;
	
	fin >> n >> m;

	for(int i=0; i<m; i++) {
		fin >> p >> a;
		farmers.push((Farmer) {p, a});
	}

	/*while (!farmers.empty()) {
		Farmer f = farmers.top();
		cout << f.p << " " << f.a << endl;
		farmers.pop();
    }*/

	int total = 0;
	int cost = 0;
	while(total < n) {
		Farmer f = farmers.top();
		if(total + f.a <= n) {
			total += f.a;
			cost += f.a*f.p;
		} else {
			int rest = n-total;
			total = n;
			cost += rest*f.p;  
		}
		farmers.pop();
	}

	cout << cost << endl;
	fout << cost << endl;

	return 0;
}
