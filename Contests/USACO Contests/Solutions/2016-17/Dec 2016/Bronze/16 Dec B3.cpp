#include <fstream>
#include <iostream>
 
using namespace std;

#define F0R(i, a) for (int i=0; i<a; i++)

char ori[10][10];
 
int main() {
    //ifstream cin ("cowsignal.in");
    //ofstream cout ("cowsignal.out");
    int M,N,K; cin >> M >> N >> K;
    F0R(i,M) F0R(j,N) cin >> ori[i][j];
    F0R(i,K*M) {
        F0R(j,K*N) cout << ori[i/K][j/K];
        cout << "\n";
    }
}