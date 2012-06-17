/*
SECTION: 1.3
NUMBER: 2
ID: voxsim2
PROG: barn1
LANG: C++
*/

/*
TEXT OF THE PROBLEM:

It was a dark and stormy night that ripped the roof and gates off the stalls that hold Farmer John's cows. Happily, many of the cows were on vacation, so the barn was not completely full.

The cows spend the night in stalls that are arranged adjacent to each other in a long line. Some stalls have cows in them; some do not. All stalls are the same width.

Farmer John must quickly erect new boards in front of the stalls, since the doors were lost. His new lumber supplier will supply him boards of any length he wishes, but the supplier can only deliver a small number of total boards. Farmer John wishes to minimize the total length of the boards he must purchase.

Given M (1 <= M <= 50), the maximum number of boards that can be purchased; S (1 <= S <= 200), the total number of stalls; C (1 <= C <= S) the number of cows in the stalls, and the C occupied stall numbers (1 <= stall_number <= S), calculate the minimum number of stalls that must be blocked in order to block all the stalls that have cows in them.

Print your answer as the total number of stalls blocked. 

Sample imput
4 50 18
3
4
6
8
14
15
16
17
21
25
26
27
30
31
40
41
42
43
*/

/*
SOLUTION OF THE PROBLEM:
We can transform this problem to a graph problem, Let me explain: When we found a some sequential stalls we can see it as a Node (in example {3-4}, {6}, {8], {14-17},... are nodes) every node have only one weighted arc to successor node with height as a jumping stall that we don't have to block (in example {3,4} have a arc with height 1 because we jump 5 to go to {6}).
In the problem we want the minimum number of stalls that must be blocked in order to block all the stalls that have cows in them, so we have M boards that leave free at least M-1 arcs, so we can sort the arcs in ascending order based on the weight, and found sequential nodes that have the smallest weighted arc in order to leave only M-1 biggest arc.

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

	for(int i=0; i<c; i++) {
		fin >> stall;
		stalls.push(stall);
	}

	fin >> last;
	last = stalls.top();
	stalls.pop();

	while(!stalls.empty()){
		stall = stalls.top();

		if(stall > last+1) {
			int jump = stall - last - 1;
			jumps.push(jump);
		}

		last = stall;
		stalls.pop();
	}

/*	while(!jumps.empty()) {
		int jump = jumps.top();
		cout << jump << endl;
		jumps.pop();
	}*/

	if(jumps.size() > m-1) {
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
