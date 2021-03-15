/**
 * Description: Chordal Graph Recognition
 * Source: 
   * https://www.cs.cmu.edu/~janh/courses/411/18/lec/03-chordal-mcs.pdf
   * https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-438-algorithms-for-inference-fall-2014/lecture-notes/MIT6_438F14_Lec14.pdf
 * Verification: https://old.yosupo.jp/problem/chordal_graph_recognition
 */

int N,M;
set<int> adj[MX];
int cnt[MX];
vi ord, rord;

vi find_path(int x, int y, int z) {
	vi pre(N,-1);
	queue<int> q; q.push(x);
	while (sz(q)) {
		int t = q.ft; q.pop();
		if (adj[t].count(y)) {
			pre[y] = t; vi path = {y};
			while (path.bk != x) path.pb(pre[path.bk]);
			path.pb(z);
			return path;
		}
		trav(u,adj[t]) if (u != z && !adj[u].count(z) && pre[u] == -1) {
			pre[u] = t;
			q.push(u);
		}
	}
	assert(0);
}

int main() {
	setIO(); re(N,M);
	F0R(i,M) {
		int a,b; re(a,b);
		adj[a].insert(b), adj[b].insert(a);
	}
	rord = vi(N,-1);
	priority_queue<pi> pq;
	F0R(i,N) pq.push({0,i});
	while (sz(pq)) {
		pi p = pq.top(); pq.pop();
		if (rord[p.s] != -1) continue;
		rord[p.s] = sz(ord); ord.pb(p.s);
		trav(t,adj[p.s]) pq.push({++cnt[t],t});
	}
	assert(sz(ord) == N);
	trav(z,ord) {
		pi big = {-1,-1}; 
		trav(y,adj[z]) if (rord[y] < rord[z]) 
			ckmax(big,mp(rord[y],y));
		if (big.f == -1) continue;
		int y = big.s;
		trav(x,adj[z]) if (rord[x] < rord[y]) if (!adj[y].count(x)) {
			ps("NO");
			vi v = find_path(x,y,z);
			ps(sz(v));
			trav(t,v) pr(t,' ');
			exit(0);
		}
	}
	ps("YES");
	reverse(all(ord));
	trav(z,ord) pr(z,' ');
}