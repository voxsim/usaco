/*
SECTION: 2.3
NUMBER: 2
ID: voxsim2
PROG: zerosum
LANG: C++
*/
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

unsigned int N;
ifstream fin ("zerosum.in");
ofstream fout ("zerosum.out");

void zerosum(int depth, string op, string sol) {
  std::ostringstream oss;
  oss << depth;
  sol += op + oss.str();

  if(depth == N) {
    int sum = 0;
    int number = 0;
    int space = 0;

    for(std::string::size_type i = sol.size()-1; i > 0; i -= 2) {
      int lnumber = sol[i] - 48;

      if(number != 0) {
        number = lnumber * pow(10, space) + number;
      } else {
        number = lnumber;
      }
 
      switch(sol[i-1]){
        case '+':
          sum = sum + number;
          number = 0;
          space = 0;
          if(i == 2) {
            sum += 1;
          }
          break;
        case '-':
          sum = sum - number;
          number = 0;
          space = 0;
          if(i == 2) {
            sum += 1;
          }
          break;
        case ' ':
          //cout << "number: " << number << " " << lnumber << " " << space << " " << i << endl;
          space++;
          if(i == 2) {
            number = 1 * pow(10, space) + number;
            sum += number;
          }
          break;
      }
      
//      cout << sol[i-1] << sol[i] << "->" << sum << endl;
    }
    
    cout << sol << " " << sum << endl;

    if(sum == 0) {
      fout << sol << endl;
    }
  } else {
    zerosum(depth+1, " ", sol);
    zerosum(depth+1, "+", sol);
    zerosum(depth+1, "-", sol);
  }
}

int main() {
    
  fin >> N;

  cout << "N: " << N << endl;

  zerosum(2, " ", "1");
  zerosum(2, "+", "1");
  zerosum(2, "-", "1");

  return 0;
}
