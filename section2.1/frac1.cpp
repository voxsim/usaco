/*
SECTION: 2.1
NUMBER: 2 
ID: voxsim2
PROG: frac1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

unsigned int N;

struct Frac {
    float num;
    float den;
};

class CompareFrac {
public:
    bool operator()(Frac& f1, Frac& f2) {
        if(f1.num / f1.den == f2.num / f2.den)
            return f1.den > f2.den;
		return f1.num / f1.den > f2.num / f2.den;
    }
};

int main() {
    ifstream fin ("frac1.in");
    ofstream fout ("frac1.out");
	
    priority_queue<Frac, vector<Frac>, CompareFrac> fracs;

    fin >> N;
    
    for(unsigned int i=1; i<=N; i++) {
        for(unsigned int  j=0; j<=i; j++) {
            Frac frac;
            frac.num = j;
            frac.den = i;
            fracs.push(frac);
        }
    }
	
    Frac last;
    while(!fracs.empty()) {
		Frac f = fracs.top();
        if(f.num / f.den != last.num / last.den) {
            fout << f.num << "/" << f.den << endl;
            last = f;
        }
		fracs.pop();
	}

    return 0;
}
