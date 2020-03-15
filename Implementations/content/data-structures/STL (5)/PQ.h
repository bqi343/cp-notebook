/**
 * Description: Priority queue w/ modification. Use for Dijkstra?
 * Source: https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_design.html
 * Verification: ?
 */

#include <ext/pb_ds/priority_queue.hpp>

void pqExample() {
	__gnu_pbds::priority_queue<int> p;
	vi act; vector<decltype(p)::point_iterator> v;
	int n = 1000000;
	F0R(i,n) { int r = rand(); act.pb(r), v.pb(p.push(r)); }
	F0R(i,n) { int r = rand(); act[i] = r, p.modify(v[i],r); }
	sort(rall(act));
	F0R(i,n) { assert(act[i] == p.top()); p.pop(); }
}
