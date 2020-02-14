/**
 * Description: Given $N$ points, returns up to $4N$ edges which are guaranteed
	* to contain a minimum spanning tree for the graph with edge weights 
	* $w(p, q) =|p.x - q.x| + |p.y - q.y|.$ Edges are in the form 
	* \texttt{\{distance, \{src, dst\}\}}. Use a
	* standard MST algorithm on the result to find the final MST.
 * Time: O(N\log N)
 * Source: KACTL
 * Verification: 
	* https://open.kattis.com/problems/gridmst
	* CSA 84 The Sprawl
	* TC 760 ComponentsForever
 */

#include "DSU (7.6).h"

vector<pair<int,pi>> manhattanMst(vpi v) {
	vi id(sz(v)); iota(all(id),0);
	vector<pair<int,pi>> ed;
	F0R(k,4) {
		sort(all(id),[&](int i, int j) { 
			return v[i].f+v[i].s < v[j].f+v[j].s; });
		map<int,int> sweep;
		trav(i,id) { // find neighbors for first octant
			for (auto it = sweep.lb(-v[i].s); 
				it != end(sweep); sweep.erase(it++)) {
				int j = it->s;
				pi d={v[i].f-v[j].f,v[i].s-v[j].s};if (d.s>d.f)break;
				ed.pb({d.f+d.s,{i,j}});
			}
			sweep[-v[i].s] = i;
		}
		trav(p,v) {
			if (k&1) p.f *= -1;
			else swap(p.f,p.s);
		}
	}
	return ed;
}
