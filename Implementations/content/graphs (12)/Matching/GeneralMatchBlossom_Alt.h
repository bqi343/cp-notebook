/**
 * Description: Variant on Gabow's Impl of Edmond's Blossom Algorithm. 
    * General unweighted max matching with 1-based indexing. If \texttt{repr[v] = 0}
    * after \texttt{solve()} returns, \texttt{v} is part of every max matching.
 * Time: O(N^3), faster in practice
 * Source: 
	* https://github.com/koosaga/DeobureoMinkyuParty
	* https://www-m9.ma.tum.de/graph-algorithms/matchings-blossom-algorithm/index_en.html
	* https://codeforces.com/blog/entry/63630
	* https://github.com/yosupo06/library-checker-problems/blob/master/graph/general_matching/sol/correct.cpp
	* https://web.eecs.umich.edu/~pettie/matching/Gabow-general-matching-1976.pdf
 * Verification: 
 	* https://codeforces.com/contest/1089 B
 	* https://www.codechef.com/problems/HAMILG
 	* https://judge.yosupo.jp/problem/general_matching
 */

struct GeneralMaxMatch {
	int N; V<vi> adj;
	vi mate, lca_aux, par, repr;
	void init(int _N) { N = _N; adj = V<vi>(N+1); 
		mate = lca_aux = par = repr = vi(N+1); }
	void ae(int x, int y) { assert(0 < min(x,y));
		adj.at(x).pb(y), adj.at(y).pb(x); }
	int get_repr(int x) { // first ancestor without par set
		if (par[repr[x]]) assert(repr[x] != x), repr[x] = get_repr(repr[x]);
		return repr[x]; // path compression
	}
	int get_lca(int x, int y) { // get lca of x and y in O(dist)
		static int timer = 0;
		for (++timer;;swap(x,y)) {
			if (x == 0) continue;
			x = get_repr(x); assert(!par[x]);
			if (lca_aux[x] == timer) return x;
			lca_aux[x] = timer; x = par[mate[x]];
		}
	}
	bool augment(int src) {
		queue<int> q; q.push(repr[src] = src);
		auto compress = [&](int x, int y, int lca) { assert(repr[lca]);
			while (get_repr(x) != lca) {
				int mx = mate[x];
				if (get_repr(x) == x) { assert(!par[x] && !repr[mx]);
					repr[x] = repr[mx] = lca, q.push(mx);
				} else assert(repr[mx]);
				par[x] = y; x = par[y = mx];
			}
		};
		while (sz(q)) {
			int x = q.ft; q.pop(); assert(repr[x]);
			for (int y: adj[x]) { int my = mate[y];
				if (repr[y]) { // compress the tree (blossom)
					int lca = get_lca(x,y);
					compress(x,y,lca), compress(y,x,lca);
				} else if (!my) { // found augmenting path!
					for (par[y] = x;y;) swap(mate[mate[y] = par[y]],y);
					par = repr = vi(N+1); // reset par and repr
					return true;
				} else if (!repr[my]) {
					par[y] = x, repr[my] = my, q.push(my);
				}
			}
		}
		return false;
	}
	int solve() {
		int ans = 0;
		FOR(i,1,N+1) if (!mate[i]) ans += augment(i);
		FOR(i,1,N+1) if (!mate[i] && !repr[i]) assert(!augment(i));
		return ans;
	}
};