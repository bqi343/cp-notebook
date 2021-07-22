/** 
 * Description: Finds topological sort of vertices from 0..n-1 starting with s and ending with t 
   * such that everything except s has neighbor to left and everything except t has neighbor to right.
   * Adds edge between s and t if it doesn't already exist.
 * Source: 
   * https://www.sciencedirect.com/science/article/abs/pii/S0020019013000288
   * https://arxiv.org/pdf/1209.0700.pdf
 * Verification: https://official.contest.yandex.ru/opencupXXI/contest/27100/problems/M/
 * Time: O(N+M)
 */

vi bipolar_orientation(vpi edges, int n, int s, int t) {
	assert(0 <= s && s < n && 0 <= t && t < n && s != t);
	edges.ins(begin(edges),mp(s,t)); 
	// necessary and sufficient condition: after adding (s,t), everything should be in one BCC
	V<vi> adj(n);
	each(e,edges) {
		assert(e.f < n && e.s < n && e.f != e.s);
		adj[e.f].pb(e.s), adj[e.s].pb(e.f);
	}
	vi visited(n,-1), par(n,-1), dfs_ord;
	V<vi> back_edges(n);
	auto dfs = y_combinator([&](auto self, int x) -> void {
		assert(visited[x] == -1);
		visited[x] = sz(dfs_ord); dfs_ord.pb(x);
		for (int y: adj[x]) {
			if (visited[y] == -1) par[y] = x, self(y);
			else if (visited[y] < visited[x]) back_edges[y].pb(x);
		}
	});
	dfs(s); if (sz(dfs_ord) != n) return {}; // >1 connected component
	vb assigned(n);
	V<vi> ears; // may contain degenerate ears
	for (int x: dfs_ord) {
		assigned.at(x) = 1;
		for (int y: back_edges[x]) {
			vi ear{x,y};
			while (!assigned.at(ear.bk)) {
				assert(par.at(ear.bk) != -1);
				assigned.at(ear.bk) = 1;
				ear.pb(par.at(ear.bk));
			}
			if (ear.bk == x && ear != vi{s,t,s}) return {}; // found a cycle
			ears.pb(ear);
		}
	}
	vi weight(n,1); // given ears, find ordering in linear time
	ROF(i,1,sz(ears)) FOR(j,1,sz(ears[i])-1) weight[ears[i][0]] += weight[ears[i][j]];
	assert(weight[s]+weight[t] == n);
	vpi ival(n,{-1,-1}); ival[s] = {0,weight[s]-1}; ival[t] = {weight[s],n-1}; 
	FOR(i,1,sz(ears)) {
		const auto& e = ears[i];
		int repr = e[0]; 
		if (ival[e.ft].f < ival[e.bk].f) {
			ROF(j,1,sz(e)-1) {
				int x = e[j];
				ival[x] = {ival[repr].s-weight[x]+1,ival[repr].s};
				ival[repr].s -= weight[x];
			}
		} else {
			ROF(j,1,sz(e)-1) {
				int x = e[j];
				ival[x] = {ival[repr].f,ival[repr].f+weight[x]-1};
				ival[repr].f += weight[x];
			}
		}
	}

	{ // check validity of solution
		F0R(i,n) assert(ival[i].f != -1 && ival[i].f == ival[i].s);
		vi distinct; F0R(i,n) distinct.pb(ival[i].f);
		sor(distinct); F0R(i,n) assert(distinct[i] == i);
		vi out(n), in(n);
		each(e,edges) {
			if (ival[e.f].f > ival[e.s].f) swap(e.f,e.s);
			++out.at(e.f), ++in.at(e.s);
		}
		F0R(i,n) {
			if (i != s) assert(in[i]);
			else assert(!in[i]);
			if (i != t) assert(out[i]);
			else assert(!out[i]);
		}
	}

	vi ordering(n,-1); F0R(i,n) ordering.at(ival[i].f) = i;
	return ordering;
}