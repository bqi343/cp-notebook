// #include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)

ifstream cin ("fortmoo.in");
ofstream cout ("fortmoo.out");

bool grid[200][200], ok1[200][200][200], ok2[200][200][200];

bool test(int l1, int l2, int w1, int w2) {
    if (!ok1[l1][l2][w1] || !ok1[l1][l2][w2] || !ok2[w1][w2][l1] || !ok2[w1][w2][l2]) return 0;
    return 1;
}

int main() {
    int N, M, ans=0;
    ios_base::sync_with_stdio(0), cin >> N >> M;
    
    F0R(i,N) F0R(j,M) {
    	char x;
    	cin >> x;
    	if (x == '.') grid[j][i] = 1;
	} 
	
	F0R(i,M) F0R(j,N) {
		ok1[i][i][j] = grid[i][j];
		FOR(i1,i+1,M) ok1[i][i1][j] = ok1[i][i1-1][j] & grid[i1][j];
	}
	F0R(j,N) F0R(i,M) {
		ok2[j][j][i] = grid[i][j];
		FOR(j1,j+1,N) ok2[j][j1][i] = ok2[j][j1-1][i] & grid[i][j1];
	}
    F0R(a,M) FOR(b,a,M) F0R(c,N) FOR(d,c,N) {
    	if ((b-a+1)*(d-c+1)>ans && test(a,b,c,d)) ans = (b-a+1)*(d-c+1);
    }
    
    cout << ans;
}