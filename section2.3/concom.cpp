/*
SECTION: 2.3
NUMBER: 5
ID: voxsim2
PROG: concom
LANG: C++
*/
/*

It is said that a company A controls company B if at least one
of the following conditions is satisfied:

  * Company A = Company B
  * Company A owns more than 50% of Company B
  * Company A controls K (K >= 1) companies denoted C_1 , ..., C_K with
    each company C_i owning x_i % of company B and x_1 + .... + x_K > 50%.

  So for each triple (i, j, p) we memorize p in a matrix, and add p to (k,j) where
  k controls i. 
*/
#include <iostream>
#include <fstream>

using namespace std;

unsigned int N;
unsigned int P[101][101];
unsigned int C[101][101];
unsigned int start = 101;
unsigned int end = 1;

void control(unsigned int i, unsigned int j) {
  if(C[i][j])
    return;

  C[i][j] = 1;

  for(unsigned int k=start; k<=end; k++) {
    P[i][k] += P[j][k];
    if(P[i][k] > 50) 
      control(i, k);
  }

  // search for company that owns i that have p % of j
  for(unsigned int k=start; k<=end; k++) {
    if(k == i || k == j) 
      continue;

    if(P[k][i] > 50) {
      P[k][j] += P[i][j];
      if(P[k][j] > 50)
        control(k, j);
    }
  }
}

int main() {
    ifstream fin ("concom.in");
    ofstream fout ("concom.out");
	
    fin >> N;
    
    unsigned int i, j, p;
    for(unsigned int r=0; r<N; r++) {
      fin >> i >> j >> p;
      P[i][j] = p;
      start = i < start ? i : start;  
      start = j < start ? j : start;  
      end = i > end ? i : end;  
      end = j > end ? j : end;  
    }

    // We need two times to see all results
    for(i=start; i<=end; i++) {
      for(j=start; j<=end; j++) {
        if(i == j)
          continue;
        if(P[i][j] > 50) {
          control(i, j);
        }
      }
    }
    
    for(i=start; i<=end; i++) {
      for(j=start; j<=end; j++) {
        if(i == j)
          continue;

        if(P[i][j] > 50) {
          fout << i << " " << j << endl;
        }
      }
    }
    return 0;
}
