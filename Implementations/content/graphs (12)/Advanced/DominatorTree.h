/**
 * Description: Used only a few times. Assuming that all nodes are 
 	* reachable from $root,$ $a$ dominates $b$ iff every path from 
 	* $root$ to $b$ passes through $a.$
 * Time: O(M\log N)
 * Source: https://tanujkhattar.wordpress.com/2016/01/11/dominator-tree-of-a-directed-graph/
 * Verification: 
 	* https://codeforces.com/gym/100513/problem/L
 	* https://open.kattis.com/problems/skiresort
 */

template<int SZ> struct Dominator {
	vi adj[SZ], ans[SZ]; // input edges, edges of dominator tree
	vi radj[SZ], child[SZ], sdomChild[SZ];
	int label[SZ], rlabel[SZ], sdom[SZ], dom[SZ], co = 0;
	int par[SZ], bes[SZ]; 
	void ae(int a, int b) { adj[a].pb(b); }
	int get(int x) { // DSU with path compression
		// get vertex with smallest sdom on path to root
		if (par[x] != x) {
			int t = get(par[x]); par[x] = par[par[x]];
			if (sdom[t] < sdom[bes[x]]) bes[x] = t;
		}
		return bes[x];
	} 
	void dfs(int x) { // create DFS tree
		label[x] = ++co; rlabel[co] = x; 
		sdom[co] = par[co] = bes[co] = co;
		each(y,adj[x]) {
			if (!label[y]) {
				dfs(y); child[label[x]].pb(label[y]); }
			radj[label[y]].pb(label[x]);
		}
	}
	void init(int root) {
		dfs(root);
		ROF(i,1,co+1) {
			each(j,radj[i]) ckmin(sdom[i],sdom[get(j)]);
			if (i > 1) sdomChild[sdom[i]].pb(i);
			each(j,sdomChild[i]) {
				int k = get(j);
				if (sdom[j] == sdom[k]) dom[j] = sdom[j];
				else dom[j] = k;
			}
			each(j,child[i]) par[j] = i;
		}
		FOR(i,2,co+1) {
			if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
			ans[rlabel[dom[i]]].pb(rlabel[i]);
		}
	}
};
