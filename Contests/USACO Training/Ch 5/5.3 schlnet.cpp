/*
ID: bqi3431
PROG: schlnet
LANG: C++11
*/

//#include<iostream>
#include<fstream>
#include<queue>
#include<vector>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

bool posi[101][101], d1[101], d2[101];
int N,ans2,co[101],numcomp;
int T[101], B[101], cT;

void f1(int x) {
	if (d1[x]) return;
	FOR	(i,1,N+1) if (posi[i][x] == 1 && posi[x][i] == 0) {
		d1[x] = 1;
		return;
	}
	cT++;
	T[co[x]] ++;
	FOR(i,1,N+1) if (posi[x][i]) d1[i] = 1;
}

void f2(int x) {
	if (d2[x]) return;
	int z = 0;
	FOR	(i,1,N+1) if (posi[x][i]) z++;
	if (z == N) {
		d2[x] = 1;
		return;
	}
	FOR	(i,1,N+1) if (posi[i][x] == 0 && posi[x][i] == 1) {
		d2[x] = 1;
		return;
	}
	B[co[x]]++;
	FOR(i,1,N+1) if (posi[x][i]) d2[i] = 1;
}

void comp(int x) {
	if (co[x]) return;
	co[x] = x;
	queue<int> todo; todo.push(x);
	while (todo.size()) {
		int f = todo.front(); todo.pop();
		FOR(i,1,N+1) if (co[i] == 0 && (posi[i][f] || posi[f][i])) {
			co[i] = x;
			todo.push(i);
		}
	}
	numcomp++;
}

int main() {
	ifstream cin ("schlnet.in");
	ofstream cout ("schlnet.out");
	cin >> N;
	FOR(i,1,N+1) {
		int S; 
		posi[i][i] = 1;
		while (cin >> S) {
			if (S == 0) break;
			posi[i][S] = 1;
		}
	}
	
	FOR(k,1,N+1) FOR(i,1,N+1) FOR(j,1,N+1) 
		if (posi[i][k] & posi[k][j]) posi[i][j] = 1;
	FOR(i,1,N+1) comp(i);
	FOR(i,1,N+1) f1(i);
	FOR(i,1,N+1) f2(i);
	if (B[1] == 0) {
		cout << "1\n0\n";
		return 0;
	}
	int ans = numcomp;
	FOR(i,1,N+1) if (T[i]) ans += max(T[i],B[i])-1;
	cout << cT << "\n" << ans << "\n";
}
