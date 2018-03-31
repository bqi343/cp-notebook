// #include<iostream>
#include<fstream>

using namespace std;

typedef long long ll;
typedef pair<int,int> pi;

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

ll MOD = 1000000007;
pi pos1[1001], pos2[1001];
ll best[1001][1001];
string d1, d2;

pi getdir(char dir) {
	if (dir == 'N') return {0,1};
    if (dir == 'S') return {0,-1};
    if (dir == 'E') return {1,0};
    return {-1,0};
}

int dist(pi a, pi b) {
	a.f -= b.f, a.s -= b.s;
    return a.f*a.f+a.s*a.s;
}

int main() {
	ifstream cin ("radio.in");
	ofstream cout ("radio.out");
	int N,M; cin >> N >> M;
	cin >> pos1[0].f >> pos1[0].s >> pos2[0].f >> pos2[0].s;
    cin >> d1 >> d2;
    F0R(i,N) {
        pi a = getdir(d1[i]);
		pos1[i+1]={pos1[i].f+a.f,pos1[i].s+a.s};
    }
    F0R(i,M) {
        pi a = getdir(d2[i]);
		pos2[i+1]={pos2[i].f+a.f,pos2[i].s+a.s};
    }
 	F0R(i,1001) F0R(j,1001) best[i][j] = MOD*MOD;
    best[0][0] = 0;
    F0R(i,N+1) F0R(j,M+1) {
		if (i != 0 || j != 0) best[i][j] += dist(pos1[i],pos2[j]);
		if (i<N) best[i+1][j] = min(best[i+1][j],best[i][j]);
		if (j<M) best[i][j+1] = min(best[i][j+1],best[i][j]);
		if (i<N && j<M) best[i+1][j+1] = min(best[i+1][j+1],best[i][j]);
    }
    cout << best[N][M];
}
