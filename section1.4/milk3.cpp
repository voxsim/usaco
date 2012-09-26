/*
SECTION: 1.4
NUMBER: 4
ID: voxsim2
PROG: milk3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int buckets[20][20][20];
int capacity_a, capacity_b, capacity_c;
int possible_capacity_c[20];
int possible_capacity_c_size;

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void pours(int a, int b, int c) {
    if(buckets[a][b][c])
        return;

    if(a == 0) { // || b == capacity_b)
        //cout << c << "\n";
        possible_capacity_c[possible_capacity_c_size] = c;
        possible_capacity_c_size++;
    }

    buckets[a][b][c] = 1;

    if(a > 0) {
        //Pours from A in C
        if(a <= capacity_c-c)
            pours(0, b, c+a);
        if(a > capacity_c-c)
            pours(a-capacity_c+c, b, capacity_c);

        //Pours from A in B
    	if(a <= capacity_b-b)
            pours(0, b+a, c);
        if(a > capacity_b-b)
            pours(a-capacity_b+b, capacity_b, c);
    }

    if(b > 0) {
    	//Pours from B in A
    	if(b <= capacity_a-a)
            pours(a+b, 0, c);
        if(b > capacity_a-a)
            pours(capacity_a, b-capacity_a+a, c);

    	//Pours from B in C
    	if(b <= capacity_c-c)
            pours(a, 0, c+b);
        if(b > capacity_c-c)
            pours(a, b-capacity_c+c, capacity_c);
    }

    if(c > 0) {
    	//Pours from C in A
        if(c <= capacity_a-a)
            pours(a+c, b, 0);
        if(c > capacity_a-a)
            pours(capacity_a, b, c-capacity_a+a);

    	//Pours from C in B
    	if(c <= capacity_b-b)
            pours(a, b+c, 0);
        if(c > capacity_b-b)
            pours(a, capacity_b, c-capacity_b+b);
    }
}

int main() {
    ofstream fout ("milk3.out");
    ifstream fin ("milk3.in");

	fin >> capacity_a >> capacity_b >> capacity_c;

    pours(0,0,capacity_c);

    qsort(possible_capacity_c, possible_capacity_c_size, sizeof(int), compare);

    for(int i=0; i<possible_capacity_c_size; i++) {
        fout << possible_capacity_c[i];
        if(i < possible_capacity_c_size-1) {
            fout << " ";
        }
    }

    fout << "\n";

	return 0;
}
