#include <iostream>
#include <fstream>

using namespace std;

typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define f first
#define s second

int N,K,R,ans,cur=0;
bool adj[100][100][4], is[100][100],visit[100][100];
int xdir[4] = {1,0,-1,0}, ydir[4] = {0,1,0,-1};

void fill(int i, int j) {
	if (i >= N || i < 0 || j >= N || j < 0) return;
	if (visit[i][j]) return;
	if (is[i][j]) cur++;
	visit[i][j] = 1;
	F0R(k,4) if (!adj[i][j][k]) fill(i+xdir[k],j+ydir[k]);
}

int main() {
	// ifstream cin ("countcross.in");
	// ofstream cout ("countcross.out");
	cin >> N >> K >> R;	
	ans = K*(K-1)/2;
	
	F0R(i,R) {
		pi a,b; cin >> a.f >> a.s >> b.f >> b.s;
		a.f--,a.s--,b.f--,b.s--;
		if (a>b) swap(a,b);
		if (a.f == b.f) {
			adj[a.f][a.s][1] = 1;
			adj[b.f][b.s][3] = 1;
		} else {
			adj[a.f][a.s][0] = 1;
			adj[b.f][b.s][2] = 1;
		}
	}
	F0R(i,K) {
		pi a; cin >> a.f >> a.s;
		a.f--,a.s--;
		is[a.f][a.s] = 1;
	}
	F0R(i,N) F0R(j,N) if (is[i][j] && !visit[i][j]) {
		cur = 0;
		fill(i,j);
		ans -= cur*(cur-1)/2;
	}
	cout << ans;
}
