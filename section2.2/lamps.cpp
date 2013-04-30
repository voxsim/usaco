/*
SECTION: 2.2
NUMBER: 4
ID: voxsim2
PROG: lamps
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

#define MAX 6

unsigned int N;
unsigned int C;
unsigned int cfs[1<<MAX];
unsigned int lon;
unsigned int loff;
unsigned int c[100];
unsigned int used[4];
unsigned int founded;
unsigned int lamp[MAX];

void check_configuration(unsigned int cf) {
    bool ok = 1;
    for(unsigned int j=0; j<lon&&ok; j++) {
        unsigned int check = MAX-((c[j]-1)%MAX)-1;
        cout << "on: " << cf << "&" << 1<<check << " = " << (cf & 1<<check) << " on " << check << " byte " << c[j] << endl;
        if((cf & 1<<check) == 0)
            ok = 0;
    }
    cout << "ok on: " << ok << endl;
    for(unsigned int j=lon; j<lon+loff&&ok; j++) {
        unsigned int check = MAX-((c[j]-1)%MAX)-1;
        cout << "off: " << cf << "&" << 1<<check << " = " << (cf & 1<<check) << " on " << check << " byte" << endl;
        if((cf & 1<<check) == 1<<check)
            ok = 0;
    }
    cout << "ok off: " << ok << endl;

    if(ok) {
        cfs[cf] = 1;
        founded++;
    }
}

void press_button(unsigned int parent, unsigned int button, unsigned int depth) {
    used[button] = 1;
    cout << "click button " << button << " on " << parent << ", depth: " << depth << endl;

    unsigned int child = parent;
    if(button == 0) child ^= 0x3F;
    if(button == 1) child ^= 0x15;
    if(button == 2) child ^= 0x2A;
    if(button == 3) child ^= 0x24;

    cout << "configuration: " << child << endl;

    // Check the configuration because turn on and off continuosly the button we
    // can reach that depth
    if(depth % 2 == C % 2) {
        check_configuration(child);
    }
    
    if(depth < C - 1) {
        for(unsigned int i=button+1; i<4; i++) { 
            if(used[i] == 0)
                press_button(child, i, depth+1);
        }
    } else {
        check_configuration(child);
    }

    used[button] = 0;
}

int main() {
    ifstream fin("lamps.in");
    ofstream fout("lamps.out");
	
    fin >> N >> C;

    int value = 0;
    do {
        fin >> value;
        if(value != -1) {
            cout << "on value: " << value << endl;
            c[lon] = value;
            lon++;
        }
    } while(value != -1);
    
    value = 0;
    do {
        fin >> value;
        if(value != -1) {
            cout << "off value: " << value << endl;
            c[lon+loff] = value;
            loff++;
        }
    } while(value != -1);

    cout << "lon: " << lon << endl;
    cout << "loff: " << loff << endl;

    unsigned int initial_configuration = (1<<MAX)-1;

    if(C == 0) {
        check_configuration(initial_configuration);
    } else {
        for(unsigned int i=0; i<4; i++) {
            used[i] = 0; 
        }
        for(unsigned int i=0; i<4; i++) {
            press_button(initial_configuration, i, 0); 
        }
    }

    if(founded == 0) {
        fout << "IMPOSSIBLE" << endl;
    } else {
        for(unsigned int i=0; i<(1<<MAX); i++) {
            unsigned int n = i;
            if(cfs[n] == 1) {
                unsigned int j=0;
                while(n >= 1) {
                    lamp[MAX-j-1] = n%2;
                    n /= 2;
                    j++;
                }
                for(unsigned int k=0; k<N; k++) {
                    fout << lamp[k%MAX];
                }
                fout << endl;
            }
        }
    }

    return 0;
}
