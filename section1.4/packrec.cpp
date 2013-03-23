/*
SECTION: 1.4
NUMBER: 1
ID: voxsim2
PROG: packrec
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#define min(a, b) a<b ? a : b
#define max(a, b) a>b ? a : b

using namespace std;

struct rect {
    unsigned int l[2];
};

struct rects {
    struct rect max;
    struct rect r[4];
    unsigned int l;
};
    
struct rect first_mode(struct rects current) {
    struct rect winner;

    //first case
    unsigned int w = 0;
    unsigned int h = 0;
    for(unsigned int i=0; i<current.l; i++) {
        w += min(current.r[i].l[0], current.r[i].l[1]);
        
        unsigned int m = max(current.r[i].l[0], current.r[i].l[1]);
        if(h < m) {
            h = m;
        }
    }
    winner.l[0] = w;
    winner.l[1] = h;
    return winner;
}

struct rects take_most_huge(struct rects current) {
    unsigned int size = 0;
    unsigned int idx = -1;
    for(unsigned int i=0; i<current.l; i++) {
        if(size < current.r[i].l[0] * current.r[i].l[1]) {
            current.max = current.r[i];
            size = current.r[i].l[0] * current.r[i].l[1];
            idx = i;
        }
    }

    if(idx < current.l-1) {
        current.r[idx] = current.r[current.l-1];
    }
    current.l = current.l-1;

    return current;
}

struct rect second_mode(struct rects current, int how_many_huge) {
    if(how_many_huge == 0) {
        return first_mode(current);
    }

    current = take_most_huge(current);
    cout << "max: " << current.max.l[0] << " " << current.max.l[1] << "\n";

    struct rect winner;
    winner.l[0] = 201;
    winner.l[1] = 201;

    struct rect local;
    local.l[0] = 0;
    local.l[1] = 0;

    struct rect result = second_mode(current, how_many_huge-1);
    cout << "result: " << result.l[0] << " " << result.l[1] << "\n";
    for(int j=0; j<2; j++) {
        local.l[0] = current.max.l[0] + result.l[j-0];
        local.l[1] = current.max.l[1] + result.l[1-j];
        cout << "local: " << local.l[0] << " " << local.l[1] << "\n";

        if(winner.l[0] * winner.l[1] > local.l[0]*local.l[1])  {
            winner.l[0] = local.l[0];
            winner.l[1] = local.l[1];
        }
    }
    
    cout << "winner: " << winner.l[0] << " " << winner.l[1] << "\n";
    return winner;
}

void process(struct rects current) {
    struct rect result;
    // first case
    /*struct rect result = first_mode(current);
    for(int i=0; i<2; i++) {
        cout << result.l[i-0] << " " << result.l[1-i] << "\n";
    }*/

    // second case
    cout << "------------SECOND CASE------------\n";
    result = second_mode(current, 1);
    cout << "res: " << result.l[0] << " " << result.l[1] << "\n"; 
    cout << "--------END SECOND CASE------------\n";

    // cout << "------------THIRD CASE------------\n";
    // third case
    // result = second_mode(current, 2);
    // cout << "res: " << result.l[0] << " " << result.l[1] << "\n"; 
    // cout << "--------END THIRD CASE------------\n";

    // cout << "------------FORTH CASE------------\n";
    // forth and fifth case
    // result = second_mode(current, 3);
    // cout << "res: " << result.l[0] << " " << result.l[1] << "\n"; 
    // cout << "--------END FORTH CASE------------\n";
}

int main() {
    ofstream fout ("packrec.out");
    ifstream fin ("packrec.in");

    struct rects start;
    start.l = 4;
    for(unsigned int i=0; i<4; i++) {
        fin >> start.r[i].l[0] >> start.r[i].l[1];
    }

    process(start);

	return 0;
}
