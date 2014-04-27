/*
SECTION: 2.3
NUMBER: 4
ID: voxsim2
PROG: money
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

unsigned int N;
unsigned int V;
unsigned int C[26];
long long M[10001];

ifstream fin ("money.in");
ofstream fout ("money.out");

int main() {
    
  fin >> V >> N;

  M[0] = 1;        

  for(int v=0; v<V; v++) {
     fin >> C[v];
  }

  for(int v=0; v<V; v++) {
     for(int n=0; n<=N; n++) {
	M[n] += (n >= C[v]) ? M[n - C[v]] : 0;
     }
  }
  
  fout << M[N] << endl;

  return 0;
}
