//#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define f first
#define s second
#define pb push_back

char grids[10][10][10], des[10][10];
int N,K;

bool test(int a1, int a2, int b1, int b2, int i1, int j1) {
	char g1[10][10];
	F0R(i,N) F0R(j,N) g1[i][j] = '.';
	F0R(i,N) F0R(j,N) if (grids[i1][i][j] == '#') {
		if (i+a1<0 || i+a1>=N || j+a2<0 || j+a2>=N) return 0;
		g1[i+a1][j+a2] = '#';
	}
	F0R(i,N) F0R(j,N) if (grids[j1][i][j] == '#') {
		if (i+b1<0 || i+b1>=N || j+b2<0 || j+b2>=N) return 0;
		if (g1[i+b1][j+b2] == '#') return 0;
		g1[i+b1][j+b2] = '#';
	}
	F0R(i,N) F0R(j,N) if (g1[i][j] != des[i][j]) return 0;
	return 1;
}

int main() {
	ifstream cin ("bcs.in");
	ofstream cout ("bcs.out");
	cin >> N >> K;
	F0R(i,N) F0R(j,N) cin >> des[i][j];
	F0R(k,K) F0R(i,N) F0R(j,N) cin >> grids[k][i][j];
	FOR(a1,-7,8) FOR(a2,-7,8) FOR(b1,-7,8) FOR(b2,-7,8) F0R(i,K) FOR(j,i+1,K) 
		if (test(a1,a2,b1,b2,i,j)) {
			cout << (i+1) << " " << (j+1);
			return 0;
		}
}
