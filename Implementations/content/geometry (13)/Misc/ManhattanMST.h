/**
 * Description: Given $N$ points, returns up to $4N$ edges which are guaranteed
	* to contain a MST for graph with edge weights $w(p,q) =|p.x-q.x|+|p.y-q.y|.$ 
	* Edges are in the form \texttt{\{dist, \{src, dst\}\}}. 
 * Time: O(N\log N)
 * Source: KACTL
 	* https://github.com/spaghetti-source/algorithm/blob/master/geometry/rectilinear_mst.cc
 * Verification: https://open.kattis.com/problems/gridmst
 */

#include "DSU (7.6).h"

// Use standard MST algorithm on the result to find the final MST.
vector<pair<int,pi>> manhattanMst(vpi v) {
	vi id(sz(v)); iota(all(id),0);
	vector<pair<int,pi>> ed;
	F0R(k,4) {
		sort(all(id),[&](int i, int j) { 
			return v[i].f+v[i].s < v[j].f+v[j].s; });
		map<int,int> sweep; // find first octant neighbors
		each(i,id) { // those in sweep haven't found neighbor yet
			for (auto it = sweep.lb(-v[i].s); 
				it != end(sweep); sweep.erase(it++)) {
				int j = it->s;
				pi d{v[i].f-v[j].f,v[i].s-v[j].s};if (d.s>d.f)break;
				ed.pb({d.f+d.s,{i,j}});
			}
			sweep[-v[i].s] = i;
		}
		each(p,v) {
			if (k&1) p.f *= -1;
			else swap(p.f,p.s);
		}
	}
	return ed;
}
