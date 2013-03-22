/*
SECTION: 1.1
NUMBER: 1
ID: voxsim2
PROG: ride
LANG: C++
COMPLEXITY: O(LEN(STR1) + LEN(STR2))
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string str1, str2;
    fin >> str1 >> str2;
    int v1=1, v2=1, a;
    for(a = 0; a!=str1.length(); ++a) {
        v1 *= (int(str1[a]) - 64);
    }
    for(a = 0; a!=str2.length(); ++a) {
        v2 *= (int(str2[a]) - 64);
    }
    if(v1 % 47 == v2 % 47) {
      fout << "GO" << endl;
    } else {
      fout << "STAY" << endl;
    }
    return 0;
}
