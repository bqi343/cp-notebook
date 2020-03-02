/**
 * Description: Given a rooted tree and a subset $S$ of nodes, compute the minimal
	* subtree that contains all the nodes by adding all (at most $|S|-1$)
	* pairwise LCA's and compressing edges.
	* Returns a list of (par, orig\_index) representing a tree rooted at 0.
	* The root points to itself.
 * Source: Simon Lindholm, KACTL
 * Time: O(|S| \log |S|)
 */

#include "LCArmq (10.2).h"

vpi treeCompress(LCA& L, vi S) {
	static vi rev; rev.rsz(L.N+1);
	auto cmp = [&](int a, int b) { return L.st[a] < L.st[b]; };
	sort(all(S),cmp);
	int m = sz(S)-1; F0R(i,m) S.pb(L.query(S[i],S[i+1]));
	sort(all(S),cmp); S.erase(unique(all(S)),end(S));
	F0R(i,sz(S)) rev[S[i]] = i;
	vpi ret = {pi(0,S[0])};
	F0R(i,sz(S)-1) ret.eb(rev[L.query(S[i],S[i+1])],S[i+1]);
	return ret;
}