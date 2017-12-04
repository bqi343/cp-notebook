/*
ID: bqi3431
PROB: nocows
LANG: C++11
*/

#include<fstream>
using namespace std;
#define FOR(i, a, b) for (int i=a; i<b; i++)

int n,h,dparr[201][201];

int main() {
	ifstream cin ("nocows.in");
	ofstream cout ("nocows.out");
	cin >> n >> h;
    FOR(i,1,201) FOR(j,1,201) {
        if (i == 1) dparr[i][j] = 1;
        FOR(k,1,i-1) dparr[i][j] = (dparr[i][j]+dparr[k][j-1]*dparr[i-1-k][j-1]) % 9901;
    }
    cout << (dparr[n][h]-dparr[n][h-1]+9901) % 9901 << "\n";
}