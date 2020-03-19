/**
 * Description: use Bellman-Ford (make sure no underflow)
 * Source: cp-algorithms
 * Verification: https://cses.fi/problemset/task/1197/
 */

vi negCyc(int n, vector<pair<pi,int>> ed) {
	vl dist(n);  vi pre(n);
	F0R(i,n) trav(t,ed) if (ckmin(dist[t.f.s],dist[t.f.f]+t.s))
		pre[t.f.s] = t.f.f;
	trav(t,ed) if (ckmin(dist[t.f.s],dist[t.f.f]+t.s)) {
		int x = t.f.s; F0R(i,n) x = pre[x];
		vi cyc; for (int v=x;v!=x||sz(cyc)>1;v=pre[v])cyc.pb(v);
		reverse(all(cyc)); return cyc;
	}
	return {};
}
