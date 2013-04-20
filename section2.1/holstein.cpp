/*
SECTION: 2.1
NUMBER: 4
ID: voxsim2
PROG: holstein
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>

using namespace std;

unsigned int V;
unsigned int G;
unsigned int min_req[25];
unsigned int feedtypes[15][25];

typedef struct {
    unsigned int idx;
    unsigned int session;
    deque<unsigned int> feeds;
    unsigned int d;
    unsigned int req[25];
} el;

queue<el> elements;

int main() {
    ifstream fin ("holstein.in");
    ofstream fout ("holstein.out");
	
    fin >> V;
    for(unsigned int i=0; i<V; i++) {
        fin >> min_req[i];
    }
    
    fin >> G;
    for(unsigned int i=0; i<G; i++) {
        for(unsigned int j=0; j<V; j++) {
            fin >> feedtypes[i][j];
        }
    }

    el e;
    e.idx = -1;
    e.session = 0;
    e.d = 0;
    for(unsigned int j=0; j<V; j++) {
        e.req[j] = 0;
    }
    elements.push(e);

    el winner;
    while(!elements.empty()) {
        el en = elements.front();

        bool min = true;
        for(unsigned int j=0; j<V && min; j++) {
            if(en.req[j] < min_req[j]) 
                min = false;
        }

        if(min) {
            winner = en;
            break;
        }

        for(unsigned int i=en.idx+1; i<G; i++) {
            el e;
            e.idx = i;
            e.session = en.session + pow(2,i);
            e.d = en.d+1;
            e.feeds = en.feeds;
            e.feeds.push_back(i);
            for(unsigned int j=0; j<V; j++) {
                e.req[j] = en.req[j] + feedtypes[i][j];
            }
            elements.push(e);
        }
        elements.pop();
    }

    fout << winner.d;
    for(deque<unsigned int>::iterator it = winner.feeds.begin(); it != winner.feeds.end(); ++it) {
        fout << " ";
        fout << (*it) + 1;
    }
    fout << endl;

    return 0;
}
