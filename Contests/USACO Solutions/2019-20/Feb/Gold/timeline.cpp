#include "bits/stdc++.h"
 
using namespace std;
 
void setIO(string s) {
	ios_base::sync_with_stdio(0); cin.tie(0); 
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}
 
#define f first
#define s second
 
const int MX = 1e5+5;
 
int N,M,C,S[MX],in[MX];
bool vis[MX];
vector<pair<int,int>> adj[MX];
queue<int> q;
 
int main() {
	setIO("timeline");
	cin >> N >> M >> C; 
	for (int i = 1; i <= N; ++i) cin >> S[i];
	for (int i = 0; i < C; ++i) {
		int a,b,x; cin >> a >> b >> x;
		adj[a].push_back({b,x}); in[b] ++;
	}
	for (int i = 1; i <= N; ++i) if (!in[i]) q.push(i);
	while (q.size()) {
		int x = q.front(); q.pop(); 
		vis[x] = 1; assert(S[x] <= M);
		for (auto& t: adj[x]) {
			S[t.f] = max(S[t.f],S[x]+t.s);
			if (!(--in[t.f])) q.push(t.f);
		}
	}
	for (int i = 1; i <= N; ++i) {
		assert(vis[i]);
		cout << S[i] << "\n";
	}
}