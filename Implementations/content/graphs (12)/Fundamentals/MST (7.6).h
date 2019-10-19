/**
 * Description: Kruskal's algorithm for minimum spanning tree
 * Time: O(M\log M)
 * Source: CSAcademy, KACTL
 * Verification: USACO superbull
 */

#include "DSU.h"

template<class T> T kruskal(int n, vector<pair<T,pi>> edge) {
	sort(all(edge));
	T ans = 0; DSU D; D.init(n);
	trav(a,edge) if (D.unite(a.s.f,a.s.s)) ans += a.f; // edge is in MST
	return ans;
}
