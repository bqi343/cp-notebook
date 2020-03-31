#include <bits/stdc++.h>
using namespace std;
 
void setIO(string s) {
	ios_base::sync_with_stdio(0); cin.tie(0); 
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}
 
const int MX = 2e5+5;
 
int N,M;
 
int par[MX],cnt[MX];
vector<int> adj[MX], rpar[MX];
queue<int> q; 
 
void merge(int a, int b) {
	a = par[a], b = par[b]; 
	if (rpar[a].size() < rpar[b].size()) swap(a,b);
	for (int t: rpar[b]) { par[t] = a; rpar[a].push_back(t); }
	adj[a].insert(end(adj[a]),begin(adj[b]),end(adj[b])); 
	adj[b].clear();
	if (adj[a].size() > 1) q.push(a);
}
 
int main() { 
	setIO("fcolor");
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int a,b; cin >> a >> b;
		adj[a].push_back(b);
	}
	for (int i = 1; i <= N; ++i) {
		par[i] = i; rpar[i].push_back(i);
		if (adj[i].size() > 1) q.push(i);
	}
	while (q.size()) {
		int x = q.front(); if (adj[x].size() <= 1) { q.pop(); continue; }
		int a = adj[x].back(); adj[x].pop_back();
		if (par[a] == par[adj[x].back()]) continue;
		merge(a,adj[x].back());
	}
	int co = 0;
	for (int i = 1; i <= N; ++i) {
		if (!cnt[par[i]]) cnt[par[i]] = ++co;
		cout << cnt[par[i]] << "\n";
	}
}