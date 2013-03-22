/*
SECTION: 1.3
NUMBER: 2
ID: voxsim2
PROG: barn1
LANG: C++
COMPLEXITY: O(c)
*/
/*
SOLUTION OF THE PROBLEM:
We can transform this problem to a graph problem, Let me explain: When we found a some sequential stalls we can see it as a Node (in example {3-4}, {6}, {8], {14-17},... are nodes). 
Every node have only one weighted arc to successor node with height as a jumping stall that we don't have to block (in example {3,4} have a arc with height 1 because we jump 5 to go to {6}).
In the problem we want to found the minimum number of stalls that must be blocked in order to block all the stalls that have cows in them, so we have M boards that leave free at least M-1 arcs, so we can sort the arcs in ascending order based on the weight, and found sequential nodes that have the smallest weighted arc in order to leave only M-1 biggest arc.

In the example we have:
{3, 4} -(1)-> {6} -(1)-> {8} -(5)-> {14-17} -(3)-> {21} -(3)-> {25-27} -(2)-> {30, 31} -(8)-> {40-43}

and we leve only -(5)->, the second -(3)-> and -(8)-> (the biggest):
{3 - 8} -(5)-> {14 - 21} -(3)-> {25-31} -(8)-> {40-43}

So we have the minimum number: 25.
*/

#include <iostream>
#include <fstream>
#include <queue>
 
using namespace std;

int main() {
    ofstream fout ("barn1.out");
    ifstream fin ("barn1.in");

	priority_queue<int, vector<int>, greater<int> > stalls;
	priority_queue<int, vector<int>, greater<int> > jumps;

	int m, s, c;
	fin >> m >> s >> c;

	int min = c;
	int stall;
	int last;

	for(int i=0; i<c; i++) { // O(c)
		fin >> stall;
		stalls.push(stall);
	}

	fin >> last;
	last = stalls.top();
	stalls.pop();

	while(!stalls.empty()){ // O(c)
		stall = stalls.top();

		if(stall > last+1) {
			int jump = stall - last - 1;
			jumps.push(jump);
		}

		last = stall;
		stalls.pop();
	}

	if(jumps.size() > m-1) { //O(c-1)
		while(jumps.size() > m-1) {
			int jump = jumps.top();
			min += jump;
			jumps.pop();
		}
	}

	cout << min << endl;
	fout << min << endl;
	return 0;
}
