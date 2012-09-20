/*
SECTION: 1.4
NUMBER: 3
ID: voxsim2
PROG: ariprog
LANG: C++
*/

/*
Text: 
An arithmetic progression is a sequence of the form a, a+b,
a+2b, ..., a+nb where n=0,1,2,3,... . For this problem, a is a
non-negative integer and b is a positive integer.
Write a program that finds all arithmetic progressions of length
n in the set S of bisquares. The set of bisquares is defined as the
set of all integers of the form p<sup>2</sup> + q<sup>2</sup> (where
p and q are non-negative integers).

Solution:
First we create the set of bisquares.
Second we limit b: a+n*b <= 2*m*m  ==> b <= (2*m*m-a)/n
In the worst case a=0 so b <= (2*m*m)/n
So we cycle for the possible values of b and for the possible values of a (the bisquares)

Complexity: O(m^2 + 2*(m^2/n)*n) = O(m^2 + 2*m^2) = O(3*m^2)
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

unsigned char exist_bisquares[125001];
unsigned int number_bisquares[125001];

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main() {
    std::ofstream fout ("ariprog.out");
    std::ifstream fin ("ariprog.in");
    int n, m;
    fin >> n >> m;
    int nbs = 0;

    for(unsigned int p=0; p<=m; p++) {
        for(unsigned int q=p; q<=m; q++) {
            if(exist_bisquares[p*p+q*q])
                continue;
            exist_bisquares[p*p+q*q] = 1;
            number_bisquares[nbs] = p*p+q*q;
            nbs++;
        }
    }
    
    qsort(number_bisquares, nbs, sizeof(int), compare);

    unsigned int a;
    unsigned int b = 1;
    unsigned int i;
    unsigned int k;
    unsigned int ok;
    unsigned int upper_bound = (2*m*m)/(n-1);
    unsigned int none = 1;

    while(b <= upper_bound) {
        for(i = 0; i<nbs; i++) {
            a = number_bisquares[i];
            ok = 1;
            for(k=1; k<n && ok && a+k*b < 2*m*m+1; k++) {
               ok = exist_bisquares[a+k*b];
            }
            if(ok && k==n) {
                fout << a << " " << b << "\n";
                none = 0;
            }
        }
        b++;
    }

    if(none) {
        fout << "NONE\n";
    }

	return 0;
}
