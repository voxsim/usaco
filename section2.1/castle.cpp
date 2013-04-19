/*
SECTION: 2.1
NUMBER: 1
ID: voxsim2
PROG: castle
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

unsigned int N;
unsigned int M;
unsigned int walls[50][50];
unsigned int rooms[50][50];
unsigned int visit[50][50];
unsigned int labels[2500];
unsigned int label;

void fill(unsigned int i, unsigned int j) {

    if(visit[i][j] == 1)
        return;

    visit[i][j] = 1;
    labels[rooms[i][j]-1]++;

    // West wall
    if((walls[i][j] & 1) == 0 && j > 0) {
        rooms[i][j-1] = rooms[i][j];
        fill(i, j-1);
    }
    
    // North wall
    if((walls[i][j] & 2) == 0 && i > 0) {
        rooms[i-1][j] = rooms[i][j]; 
        fill(i-1, j);
    }
   
    // East wall
    if((walls[i][j] & 4) == 0 && j < M-1) {
        rooms[i][j+1] = rooms[i][j]; 
        fill(i, j+1);
    }
   
    // South wall
    if((walls[i][j] & 8) == 0 && i < N-1) {
        rooms[i+1][j] = rooms[i][j]; 
        fill(i+1, j);
    }
}

int main() {
    ifstream fin ("castle.in");
    ofstream fout ("castle.out");
	
    fin >> M >> N;
    
    for(unsigned int i=0; i<N; i++) {
        for(unsigned int j=0; j<M; j++) {
            fin >> walls[i][j];
        }
    }

    label = 1;
    
    // Mark every square with the label room
    for(unsigned int i=0; i<N; i++) {
        for(unsigned int j=0; j<M; j++) {
            if(rooms[i][j] == 0) {
                rooms[i][j] = label;
                label++;
                fill(i, j);
            }
        }
    }

    for(unsigned int i=0; i<N; i++) {
        for(unsigned int j=0; j<M; j++) {
            cout << rooms[i][j] << " ";
        }
        cout << endl;
    }
   
    // Get the size of the largest room
    unsigned int maxRoom = 0;
    for(unsigned int i=0; i<label; i++) {
        if(maxRoom < labels[i]) {
            maxRoom = labels[i];
        }
    }

    unsigned int ci = 0;
    unsigned int cj = 0;
    char d = 'E';
    unsigned int maxRoomCreat = 0;
   
    // Found the wall to remove to have the largest room creatable
    for(unsigned int i=0; i<N; i++) {
        for(unsigned int j=0; j<M; j++) {

            // Choose N instead of E
            // North wall
            if((walls[i][j] & 2) == 2 && i > 0) {
                if(rooms[i-1][j] != rooms[i][j]) {
                    unsigned int maxRoomCreatL = labels[rooms[i-1][j]-1] + labels[rooms[i][j]-1];

                    // if tied
                    if(maxRoomCreat == maxRoomCreatL) {
                        // choose the nearest at west
                        if(j < cj-1) {
                            ci = i+1;
                            cj = j+1;
                            d = 'N';
                        }

                        // choose the nearest at south
                        if(j == cj-1 && i > ci-1) {
                            ci = i+1;
                            cj = j+1;
                            d = 'N';
                        }
                    }
                    
                    if(maxRoomCreat < maxRoomCreatL){
                        maxRoomCreat = maxRoomCreatL;
                        ci = i+1;
                        cj = j+1;
                        d = 'N';
                    }
                    
                    
                }
            }
           
            // East wall
            if((walls[i][j] & 4) == 4 && j < M-1) {
                if(rooms[i][j+1] != rooms[i][j]) {
                    unsigned int maxRoomCreatL = labels[rooms[i][j+1]-1] + labels[rooms[i][j]-1];

                    // if tied
                    if(maxRoomCreat == maxRoomCreatL) {
                        // choose the nearest at west
                        if(j < cj-1) {
                            ci = i+1;
                            cj = j+1;
                            d = 'E';
                        }

                        // choose the nearest at south
                        if(j == cj-1 && i > ci-1) {
                            ci = i+1;
                            cj = j+1;
                            d = 'E';
                        }
                    }

                    if(maxRoomCreat < maxRoomCreatL){
                        maxRoomCreat = maxRoomCreatL;
                        ci = i+1;
                        cj = j+1;
                        d = 'E';
                    }
                }
            }
        }
    }

    fout << label-1 << endl;
    fout << maxRoom << endl;
    fout << maxRoomCreat << endl;
    fout << ci << " " << cj << " " << d << endl;
    return 0;
}
