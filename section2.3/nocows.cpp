/*
SECTION: 2.3
NUMBER: 2
ID: voxsim2
PROG: nocows
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

unsigned int N;
unsigned int K;
unsigned int D[201][101];

ifstream fin ("nocows.in");
ofstream fout ("nocows.out");

int main() {
    
  fin >> N >> K;

  D[1][1] = 1;

  for(int k=2; k<=K; k++) {
     int total = (int) pow(2, k-1);
     for(int n=2; n<=total; n += 2) {
        for(int j=0; j<=N; j++) {
	   if(D[j][k-1] != 0) {
	   	D[j+n][k] += D[j][k-1]*total/n;
	   	cout << "[" << j+n << "][" << k << "] [" << j << "][" << k-1 << "]: " << D[j][k-1] << " " << D[j+n][k] << " " << total << endl;
	   }
	} 
     }
  }

  
  for(int k=0; k<=K; k++) {
     for(int n=0; n<=N; n++) {
	cout << "D["<<n<<"]["<<k<<"]: "<< D[n][k] << endl;
     }
  }

  fout << D[N][K]%9901 << endl;

  return 0;
}
