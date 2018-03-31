// #include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>

using namespace std;
 
typedef vector<int> vi;
typedef pair<int,int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second

const int MOD = 1000000007;

ifstream cin ("vacationgold.in");
ofstream cout ("vacationgold.out");

int N,M,K,Q, dist[200][200], co = 0, sum = 0;
int f[200][20001], t[200][20001];
vi h;
unordered_map<int,int> hub;
vector<pair<pi,int>> edge;
vector<pi> from[20001], to[20001];

void init() {
	cin >> N >> M >> K >> Q;
	F0R(i,K) F0R(j,K) {
		dist[i][j] = MOD;
		if (i == j) dist[i][j] = 0;
	}
	F0R(i,M) {
		int u,v,w; cin >> u >> v >> w;
		edge.pb({{u,v},w});
	}
	h.resize(K);
	F0R(i,K) {
		cin >> h[i];
		hub[h[i]] = i;
	}
	for (auto a: edge) {
		if (hub.count(a.f.f) == 0) from[a.f.f].pb({hub[a.f.s],a.s});
		else if (hub.count(a.f.s) == 0) to[a.f.s].pb({hub[a.f.f],a.s});
		else dist[hub[a.f.f]][hub[a.f.s]] = a.s;
	}
	FOR(i,1,N+1) for(auto x: to[i]) for (auto y: from[i]) 
		dist[x.f][y.f] = min(dist[x.f][y.f],x.s+y.s);
		
	F0R(k,K) F0R(i,K) F0R(j,K) 
		dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
		
	F0R(i,200) F0R(j,20001) f[i][j] = t[i][j] = MOD;
	FOR(i,1,N+1) {
	    for (auto a: from[i]) F0R(j,K) f[j][i] = min(f[j][i], a.s+dist[a.f][j]);
	    for (auto a: to[i]) F0R(j,K) t[j][i] = min(t[j][i], dist[j][a.f]+a.s);
	}
}

int main() {
	init();
	F0R(i,Q) {
		int a,b; cin >> a >> b;
		int cur = MOD;
		if (hub.count(a) == 1 && hub.count(b) == 1) {
			cur = dist[hub[a]][hub[b]];
		} else if (hub.count(a) == 1) {
			for (auto y: to[b])
				cur = min(cur,dist[hub[a]][y.f]+y.s);
		} else if (hub.count(b) == 1) {
			for (auto x: from[a])
				cur = min(cur,x.s+dist[x.f][hub[b]]);
		} else {
		    F0R(j,K) cur = min(cur,f[j][a]+t[j][b]);
		}
		
		if (cur < MOD) co ++, sum += cur;
	}
	cout << co << "\n" << sum;
}
