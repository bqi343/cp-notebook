/**
 * Description: offline dynamic connectivity
 * Source: own
 * Verification: https://codeforces.com/contest/1140/problem/F
 */

#include "DSUrb (15.5).h"

template<int SZ> struct DynaCon { 
	DSUrb D; vpi seg[2*SZ];
	void upd(int l, int r, pi p) {	// add edge p to all times in interval [l, r]
		for (l += SZ, r += SZ+1; l < r; l /= 2, r /= 2) {
			if (l&1) seg[l++].pb(p);
			if (r&1) seg[--r].pb(p);
		}
	}
	void process(int ind) {
		each(t,seg[ind]) D.unite(t.f,t.s);
		if (ind >= SZ) {
			// do stuff with D at time ind-SZ
		} else process(2*ind), process(2*ind+1);
		each(t,seg[ind]) D.rollback();
	}
};
