/**
 * Description: Tree decomposition of width 2. Just keep removing 
 	* verts with degree at most 2.
 * Time: O((N+M)\log N)
 * Source: 
 	* https://chaoxuprime.com/posts/2015-04-10-treewidth-2.html
 	* https://github.com/yosupo06/library-checker-problems/blob/438f473c1a5eb22de1d595fc0486c1e3d78e3efe/graph/tree_decomposition_width_2/sol/correct.cpp
 * Verifcation: https://judge.yosupo.jp/problem/tree_decomposition_width_2
 */

int N,M;
str tmp;
set<int> adj[MX];
vector<vi> seq;
bool done[MX];

int main() {
	setIO(); re(tmp,tmp,N,M);
	F0R(i,M) {
		int u,v; re(u,v);
		adj[u].insert(v), adj[v].insert(u);
	}
	queue<int> q; FOR(i,1,N+1) q.push(i);
	while (sz(q)) {
		int x = q.ft; q.pop(); 
		if (sz(adj[x]) > 2 || done[x]) continue;
		done[x] = 1;
		each(t,adj[x]) adj[t].erase(x);
		if (sz(adj[x]) == 0) {
			seq.pb({0,x,-1,-1});
		} else if (sz(adj[x]) == 1) {
			int u = *begin(adj[x]);
			seq.pb({1,x,u,-1});
			q.push(u);
		} else if (sz(adj[x]) == 2) {
			int u = *begin(adj[x]);
			int v = *adj[x].rbegin();
			seq.pb({2,x,u,v});
			adj[u].insert(v), adj[v].insert(u);
			q.push(u), q.push(v);
		}
	}
	if (sz(seq) != N) { ps(-1); exit(0); }
	reverse(all(seq));
	int id = -1;
	vi par(N+1), vert(N+1);
	vector<vi> bag(N);
	map<pi,int> edge;
	each(t,seq) {
		int v = t[1];
		auto ad = [&](int a, int b, int c) {
			if (a > b) swap(a,b);
			edge[{a,b}] = c;
		};
		id ++;
		if (t[0] == 0) {
			bag[id] = {v};
			par[id] = id-1;
		} else if (t[0] == 1) {
			bag[id] = {t[2],v};
			par[id] = vert[t[2]];
			ad(t[2],v,id);
		} else if (t[0] == 2) {
			pi p = {t[2],t[3]}; if (p.f > p.s) swap(p.f,p.s);
			bag[id] = {p.f,p.s,v};
			par[id] = edge[p];
			ad(p.f,p.s,id); ad(p.f,t[1],id); ad(p.s,t[1],id);
		}
		vert[t[1]] = id;
	}
	ps("s","td",N,2,N);
	F0R(i,N) {
		pr("b ",i+1);
		each(t,bag[i]) pr(' ',t);
		ps();
	}
	FOR(i,1,N) ps(par[i]+1,i+1);
}
