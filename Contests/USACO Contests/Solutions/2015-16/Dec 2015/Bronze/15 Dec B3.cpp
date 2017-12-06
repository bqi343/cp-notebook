// #include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

ofstream cout ("badmilk.out");
ifstream cin ("badmilk.in");

int a[51][51], badmilk[51];

int main() {
    int N, M, D, S, max1 = 0;
    cin >> N >> M >> D >> S;
    for (int i = 1; i <= M; ++i) {
        badmilk[i] = 1;
    }
    
    for (int i = 0; i <= 50; ++i) {
        for (int j = 0; j <= 50; ++j) {
            a[i][j] = 101;
        }
    }
    for (int i = 0; i < D; ++i) {
        int p, m, t;
        cin >> p >> m >> t;
        a[p][m] = t;
    }
    
    for (int i = 0; i < S; ++i) {
        int p, t;
        cin >> p >> t;
        
        for (int j = 1; j <= M; ++j) {
            if (a[p][j] >= t) {
                badmilk[j] = 0;
            }
        }
    }
    
    
    for (int i = 1; i <= M; ++i) {
        if (badmilk[i] == 1) {
            int count = 0;
            for (int j = 1; j <= N; ++j) {
                if (a[j][i] != 101) {
                    count ++;
                }
            }
            if (count > max1) max1 = count;
        }
    }
    cout << max1;
}
