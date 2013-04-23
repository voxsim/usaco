/*
SECTION: 2.2
NUMBER: 3
ID: voxsim2
PROG: runround
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

unsigned int M;
char strM[10];
unsigned int lenM;
unsigned int used[10];
unsigned int unique[10];
bool stop;
bool firstTime;

void nextUnique(unsigned int depth, unsigned int maxDepth) {
    if(stop) {
        return;
    }

    if(depth >= maxDepth) {
        /*for(unsigned int i=0; i<maxDepth; i++) {
            cout << unique[i];
        }
        cout << endl;*/

        unsigned int usedrun[10];
        for(unsigned int i=0; i<maxDepth; i++) {
            usedrun[i] = 0;
        }

        unsigned int count = 0;
        unsigned int start = 0;
        //cout << "checking: " << unique[0] << endl;
        while(!usedrun[start]) {
            usedrun[start] = 1;
            count++;
            start = (start + unique[start]) % maxDepth;
            //cout << "checking: " << unique[start] << " " << usedrun[start] << " " << count << " " << maxDepth << endl;
        }

        if(count == maxDepth && start == 0) {
            stop = true;
        }
        firstTime = false;
        return;
    }
        
    unsigned int i;

    if(firstTime) {
        i = (unsigned int) strM[depth] - 48;
    } else {
        i = 1;
    }

    for(; i<10&&!stop; i++) {
        if(used[i] == 0) {
            used[i] = 1;
            unique[depth] = i;
            nextUnique(depth+1, maxDepth);
            used[i] = 0;
        }
    }

    firstTime = false;
}

int main() {
    ifstream fin ("runround.in");
    ofstream fout ("runround.out");
	
    fin >> M;

    lenM = sprintf(strM, "%d", M+1);

    //cout << lenM << endl;
    //cout << strM << endl;

    stop = false;
    firstTime = true;
    unsigned int lastD;

    for(unsigned int d=lenM; d<10&&!stop; d++) {
        unsigned int i;

        if(firstTime) {
            i = (unsigned int) strM[0] - 48;
        } else {
            i = 1;
        }

        //cout << "i: " << i << endl;

        for(; i<10&&!stop; i++) {
            used[i] = 1;
            unique[0] = i;
            nextUnique(1, d);
            used[i] = 0;
        }
        lastD = d;
    }
    
    if(stop) {
        for(unsigned int i=0; i<lastD; i++) {
            fout << unique[i];
        }
        fout << endl;
    } else {
        fout << "ERROR" << endl;
    }

    return 0;
}
